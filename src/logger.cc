#include "logger.h"
#include <time.h>
#include <iostream>

// 懒汉式
Logger& Logger::GetInstance()
{
    static Logger logger;
    return logger;
}

Logger::Logger()
{
    // 启动专门写日志的线程
    std::thread writeLogTask([&](){
        for(;;)
        {
            // 获取当前日期
            time_t now = time(nullptr);
            tm *nowtm = localtime(&now);

            // 组织文件名
            char file_name[128] = {0};
            sprintf(file_name,"%d-%d-%d-log.txt", nowtm->tm_year + 1900, nowtm->tm_mon + 1, nowtm->tm_mday);

            FILE *pf = fopen(file_name, "a+");
            if(pf == nullptr)
            {
                std::cout << "logger file:" << file_name << "open error!" << std::endl;
                exit(EXIT_FAILURE);
            }

            // 往文件中写日志
            std::string msg = m_lckQue.Pop();

            char time_buf[128] = {0};
            sprintf(time_buf, "%d:%d:%d=>[%s]",
                    nowtm->tm_hour,
                    nowtm->tm_min,
                    nowtm->tm_sec,
                    (m_loglevel == INFO ? "INFO" : "ERROR"));
            msg.insert(0, time_buf); // 消息前面加上时间 和 日志级别
            msg.append("\n"); 

            fputs(msg.c_str(), pf);
            fclose(pf); // 写一行日志就关闭文件
        }
    });
    //
    writeLogTask.detach();
}


void Logger::setLogLevel(LogLevel level)
{
    m_loglevel = level;
}
void Logger::Log(std::string msg)
{
    m_lckQue.Push(msg);
}