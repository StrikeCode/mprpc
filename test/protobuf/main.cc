#include "test.pb.h"
#include <iostream>
#include <string>
using namespace fixbug; // 工作中不要这样！！防止命名空间污染

int main()
{
    // LoginResponse rsp;
    // // 对象成员的修改方法，要先获取成员的指针
    // ResultCode *rc = rsp.mutable_result();
    // rc->set_errcode(1);
    // rc->set_errmsg("登录失败");

    GetFriendListsResponse rsp;
    ResultCode *rc = rsp.mutable_result();
    rc->set_errcode(0);
   
    User *user1 = rsp.add_friend_list(); // 返回一个指向User类型指针，我们往里填数据就是在新的位置加入元素了
    user1->set_name("zhangsan");
    user1->set_age(20);
    user1->set_sex(User::MAN);

    User *user2 = rsp.add_friend_list(); // 返回一个指向User类型指针，我们往里填数据就是在新的位置加入元素了
    user2->set_name("lisi");
    user2->set_age(21);
    user2->set_sex(User::MAN);

    //std::cout << rsp.friend_list_size() << std::endl;

    // 打印列表元素
    int n = rsp.friend_list_size();
    for(int i = 0; i < n; ++i)
    {
        std::cout << rsp.friend_list(i).name() << " "<< rsp.friend_list(i).age() << " " << rsp.friend_list(i).sex() << std::endl;
    }
    return 0;
}

int main1()
{
    // 封装login请求对象的数据
    LoginRequest req;
    req.set_name("lisi");
    req.set_pwd("123456");

    std::string send_str;
    // 将成员值序列化为字符串
    if(req.SerializeToString(&send_str))
    {
        std::cout << send_str.c_str() << std::endl;
    }

    // 从send_str反序列化一个login请求对象
    LoginRequest reqB;
    if(reqB.ParseFromString(send_str))
    {
        std::cout << reqB.name() << std::endl;
        std::cout << reqB.pwd() << std::endl;
    }

    return 0;
}