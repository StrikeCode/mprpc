#pragma once
#include <string>
#include "lockqueue.h"

class Logger;
// 提供用户使用日志模块的宏定义方法 ,LOG_INFO("xxx %d %s", 20, "abc")
#define LOG_INFO(fmt, ...)                         \
    do                                             \
    {                                              \
        Logger &logger = Logger::GetInstance();    \
        logger.setLogLevel(INFO);                  \
        char c[1024] = {0};                        \
        sprintf(c, fmt, ##__VA_ARGS__);            \
        logger.Log(c);                             \
    } while (0)

#define LOG_ERROR(fmt, ...)                         \
    do                                             \
    {                                              \
        Logger &logger = Logger::GetInstance();    \
        logger.setLogLevel(ERROR);                 \
        char c[1024] = {0};                        \
        sprintf(c, fmt, ##__VA_ARGS__);            \
        logger.Log(c);                             \
    } while (0)

// 定义日志级别
enum LogLevel
{
    INFO,
    ERROR,
};

// 单例类
class Logger
{
public:
    static Logger &GetInstance();
    void setLogLevel(LogLevel level);
    void Log(std::string msg);

private:
    int m_loglevel;
    LockQueue<std::string> m_lckQue; // 日志缓冲队列

    Logger();
    // 拷贝构造和移动构造
    Logger(const Logger &) = delete;
    Logger(Logger &&) = delete;
};