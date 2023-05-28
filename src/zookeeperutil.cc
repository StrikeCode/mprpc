#include "zookeeperutil.h"
#include "mprpcapplication.h"
#include <semaphore.h>
#include <iostream>

// path 就是所监视的路径，该路径下子节点发生改变就会触发调用该函数
void global_watcher(zhandle_t *zh, int type,
                    int state, const char *path, void *watcherCtx)
{
    if(type == ZOO_SESSION_EVENT) // 回调消息类型是会话相关事件
    {
        if(state == ZOO_CONNECTED_STATE) //zkclient和zkserver连接成功
        {
            sem_t *sem = (sem_t*)zoo_get_context(zh); //
            sem_post(sem); // 唤醒 Start()
        }
    }
}

ZkClient::ZkClient() : m_zhandle(nullptr)
{
}

ZkClient::~ZkClient()
{
    if (m_zhandle != nullptr)
    {
        zookeeper_close(m_zhandle);
    }
}
// zkclient启动连接 zkserver
void ZkClient::Start()
{
    std::string ip = MprpcApplication::getInstance().getConfig().Load("zookeeperip");
    std::string port = MprpcApplication::getInstance().getConfig().Load("zookeeperport");
    std::string connstr = ip + ":" + port;

    // zookeeper_mt 多线程版本
    // zookeeper的API客户端程序提供了三个线程
    // API调用线程
    // 网络IO线程,poll,客户端不需要高并发不需要epoll
    // watcher回调线程 pthread_create
    m_zhandle = zookeeper_init(connstr.c_str(), global_watcher, 30000, nullptr, nullptr, 0);
    if (nullptr == m_zhandle)
    {
        std::cout << "zookeeper_init error!" << std::endl;
        exit(EXIT_FAILURE);
    }

    sem_t sem;
    sem_init(&sem, 0, 0);
    zoo_set_context(m_zhandle, &sem);
    // 等待watcher回调线程执行完任务才会退出这里的wait
    sem_wait(&sem);
    std::cout << "zookeeper_init success!" << std::endl;
}
// 在zkserver上根据指定的path创建znode节点
void ZkClient::Create(const char *path, const char *data, int datalen, int state)
{
    char path_buffer[128];
    int bufferlen = sizeof(path_buffer);
    int flag;
    // 先判断path表示的znode节点是否存在，若存在，就不用重复创建
    flag = zoo_exists(m_zhandle, path, 0, nullptr);
    if (ZNONODE == flag) // 表示path的znode节点不存在
    {
        // 创建指定path的znode节点
        flag = zoo_create(m_zhandle, path, data, datalen,
                          &ZOO_OPEN_ACL_UNSAFE, state, path_buffer, bufferlen);
        if (flag == ZOK)
        {
            std::cout << "znode create success ... path:" << path << std::endl;
        }
        else
        {
            std::cout << "flag:" << flag << std::endl;
            exit(EXIT_FAILURE);
        }
    }
}
// 根据参数指定的znode节点路径，查找znode的值
std::string ZkClient::GetData(const char *path)
{
    char buffer[64];
    int bufferlen = sizeof(buffer);
    // 执行后，buffer 和bufferlen会被写入数据
    int flag = zoo_get(m_zhandle, path, 0, buffer, &bufferlen, nullptr);
    if (flag != ZOK)
    {
        std::cout << "get znode error... path:" << path << std::endl;
        return "";
    }
    else 
    {
        return buffer;
    }
}