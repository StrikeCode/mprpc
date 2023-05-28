#pragma once

#include <unordered_map>
#include <string>

// rpcserverip rpcserverport zookeeperip zookeeperport

// 用于读取配置文件的类
class MprpcConfig
{
public:
    // 解析加载配置项文件
    void LoadConfig(const char *config_file);
    // 查询配置项信息
    std::string Load(const std::string &key);
private:
    std::unordered_map<std::string, std::string> m_configMap;
    // 去除字符串前后空格
    void Trim(std::string &src_buf);
};