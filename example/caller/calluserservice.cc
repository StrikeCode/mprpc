// 客户端使用mprpc框架业务代码，主要做发起调用的请求
#include <iostream>
#include "mprpcapplication.h"
#include "mprpcchannel.h"
#include "user.pb.h"

int main(int argc, char **argv)
{
    // 1.程序启动后，想使用mprpc框架提供的rpc服务调用，一定要先调用框架的初始化函数
    MprpcApplication::Init(argc, argv);

    // 演示调用远程发布的rpc方法Login
    fixbug::UserServiceRpc_Stub stub(new MprpcChannel());
    // rpc方法请求参数组织
    fixbug::LoginRequest request;
    request.set_name("li si");
    request.set_pwd("123456");
    // rpc方法的响应
    fixbug::LoginResponse response;
    // 发起rpc方法调用，同步的rpc调用过程
    // 底层都是转发到RpcChannel::CallMethod方法多态调用
    // 所以要实现一个继承自 RpcChannel 的类，并重写CallMethod方法
    stub.Login(nullptr, &request, &response, nullptr);

    // 一次rpc 调用完成，读调用的结果
    if (0 == response.result().errcode())
    {
        std::cout << "rpc login success:" << response.success() << std::endl;
    }
    else 
    {
        std::cout << "rpc login response error :" << response.result().errmsg() << std::endl;
    }

    fixbug::RegisterRequest request2;
    request2.set_id(4099);
    request2.set_name("zhang san");
    request2.set_pwd("888888");
    // rpc方法的响应
    fixbug::RegisterResponse response2;
    // 发起rpc方法调用，同步的rpc调用过程
    // 底层都是转发到RpcChannel::CallMethod方法多态调用
    // 所以要实现一个继承自 RpcChannel 的类，并重写CallMethod方法
    stub.Register(nullptr, &request2, &response2, nullptr);

    // 一次rpc 调用完成，读调用的结果
    if (0 == response2.result().errcode())
    {
        std::cout << "rpc register success:" << response2.success() << std::endl;
    }
    else 
    {
        std::cout << "rpc register response error :" << response2.result().errmsg() << std::endl;
    }

    return 0;
}