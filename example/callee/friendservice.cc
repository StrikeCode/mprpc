#include <iostream>
#include <string>
#include "friend.pb.h"
#include "mprpcapplication.h"
#include "rpcprovider.h"
#include <vector>

// FriendService 是一个本地服务，提供了两个进程内的本地方法Login和GetFriendLists
class FriendService : public fixbug::FriendServiceRpc // 使用在rpc服务的发布端（rpc服务提供者）
{
public:
    std::vector<std::string> GetFriendsList(uint32_t userid)
    {
        std::cout << "do GetFriendList service! userid:" << userid << std::endl;
        std::vector<std::string> vec;
        vec.push_back("Jiang tao");
        vec.push_back("shao pin");
        vec.push_back("shao an");
        return vec;
    }

    // 重写基类方法
    void GetFriendsList(::google::protobuf::RpcController *controller,
                        const ::fixbug::GetFriendsListRequest *request,
                        ::fixbug::GetFriendsListResponse *response,
                        ::google::protobuf::Closure *done)
    {
        // 1.框架给业务上报了请求参数 GetFriendsListRequest ，应用获取相应数据做本地业务
        uint32_t userid = request->userid();
        // 2.做业务
        std::vector<std::string> friendsList = GetFriendsList(userid);

        // 3.把响应写入
        fixbug::ResultCode *code = response->mutable_result();
        code->set_errcode(0);
        code->set_errmsg("");
        for(std::string &name : friendsList)
        {
            std::string *p = response->add_friends();
            *p = name;
        }

        // 4.做回调操作,执行响应对象数据的序列化和网络发送（都是由框架完成）
        done->Run();
    }
};

int main(int argc, char **argv)
{
    // 调用框架的初始化操作
    MprpcApplication::Init(argc, argv);

    // provider是一个rpc网络服务对象，把UserService对象发布到rpc节点上
    RpcProvider provider;
    provider.NotifyService(new FriendService());

    // 启动一个rpc服务发布节点，Run之后，进程进入阻塞状态，等待远程rpc调用请求
    provider.Run();
    return 0;
};