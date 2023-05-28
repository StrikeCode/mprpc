#pragma once
#include <queue>
#include <thread>
#include <mutex> 
#include <condition_variable>

// 模板类的声明和成员函数实现最好都是实现在同一个头文件
// 分文件编写可能造成链接错误
// 异步写日志使用的队列
// 生产者消费者模型
template<typename T>
class LockQueue
{
public:
    // producer
    void Push(const T &data)
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_queue.push(data);
        m_cond.notify_one(); // 消费者只有一个写线程
    }

    // 一个写线程读日志queue，将其写入磁盘中的日志文件
    T Pop()
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        while(m_queue.empty()) // 防止虚假唤醒
        {
            // 日志队列为空，进入wait状态
            m_cond.wait(lock);
        }
        T data = m_queue.front();
        m_queue.pop();
        return data;
    }
private:
    std::queue<T> m_queue;
    std::mutex m_mutex;
    std::condition_variable m_cond;
};