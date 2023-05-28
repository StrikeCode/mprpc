#pragma once

#include "mprpcconfig.h"
#include "mprpcchannel.h"
#include "mprpccontroller.h"

// RPC框架的基础类
// singleton
class MprpcApplication
{
public:
    static void Init(int argc, char **argv);
    static MprpcApplication& getInstance();
    static MprpcConfig& getConfig();
private:
    static MprpcConfig m_config;

    MprpcApplication(){}
    MprpcApplication(const MprpcApplication&) = delete;
    MprpcApplication(MprpcApplication&&) = delete;
};