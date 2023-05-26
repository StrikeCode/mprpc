#include "mprpcconfig.h"

#include <iostream>
#include <string>

// 解析加载配置项文件
void MprpcConfig::LoadConfig(const char *config_file)
{
    FILE *pf = fopen(config_file, "r");
    if(nullptr == pf)
    {
        std::cout << config_file << " is not exist" << std::endl;
        exit(EXIT_FAILURE);
    }

    while(!feof(pf))
    {
        char buf[512] = {0};
        fgets(buf, 512, pf);

        std::string read_buf(buf);
        Trim(read_buf); // 去掉前后空格

        // 判断#的注释
        if(read_buf[0] == '#' || read_buf.empty())
        {
            continue;
        }

        // 解析配置项
        int idx = read_buf.find('=');
        if(idx == -1)
        {
            continue;
        }

        std::string key;
        std::string value;
        key = read_buf.substr(0, idx);
        Trim(key);
        int endidx = read_buf.find('\n', idx);
        value = read_buf.substr(idx + 1, endidx - idx - 1);
        Trim(value);
        m_configMap.insert({key, value});
    }

    fclose(pf);
}
    // 查询配置项信息
std::string MprpcConfig::Load(const std::string &key)
{
    auto it = m_configMap.find(key);
    if(it == m_configMap.end())
    {
        return "";
    }
    return it->second;
}

// 去掉前后的空格
void MprpcConfig::Trim(std::string &src_buf)
{
    // 去前面的空格
    int idx = src_buf.find_first_not_of(' ');
    if(idx != -1)
    {
        src_buf = src_buf.substr(idx, src_buf.size() - idx);
    }

    // 去掉后面的空格
    idx = src_buf.find_last_not_of(' ');
    if(idx != -1)
    {
        src_buf = src_buf.substr(0, idx + 1);
    }
}

