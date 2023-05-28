#pragma once
#include <google/protobuf/service.h>
#include <string>

class MprpcController : public google::protobuf::RpcController
{
public:
    MprpcController();
    void Reset();
    bool Failed() const;
    std::string ErrorText() const;

    void SetFailed(const std::string &reason);

    // 未实现具体功能
    void StartCancel();
    bool IsCanceled() const;
    void NotifyOnCancel(google::protobuf::Closure *callback);

private:
    bool m_failed;  // RPC方法执行过程中的【状态】,true 标识有错误
    std::string m_errText; // RPC 方法执行过程中的【错误】
};