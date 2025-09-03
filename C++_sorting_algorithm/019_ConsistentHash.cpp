#include <iostream>
#include <list>
#include <set>
using namespace std;
#include <string>
#include "md5.h"
#include <sstream>
#include <iomanip>
#include <map>

// 一致性哈希环的取值类型
using uint = unsigned int;

// 物理节点的前置声明
class PhysicalHost;


// 虚拟节点
class VirtualHost
{
public:
    VirtualHost(string ip, PhysicalHost* p)
        : ip_(ip)
        , physicalhost_(p) 
    {
        md5_ = getMD5Hash(ip_);
    }

    // 为set容器提供比较操作符
    bool operator<(const VirtualHost& host) const 
    {
        return md5_ < host.md5_;
    }

        // 为set容器提供比较操作符
    bool operator==(const VirtualHost& host) const 
    {
        return ip_ == host.ip_;
    }

    uint getMD5() const
    {
        return md5_;
    }

    const PhysicalHost* getPhysicalHost() const
    {
        return physicalhost_;
    }

private:
    string ip_; // 虚拟节点的ip信息
    PhysicalHost* physicalhost_;  // 虚拟节点隶属的物理节点
    uint md5_; // 虚拟节点在一致性哈希环上的位置
};

// 物理节点
class PhysicalHost
{
public:
    PhysicalHost(string ip, int virtualhostnum)
        : ip_(ip)
    {
        // 虚拟节点需要一个ip，还需要记录它属于哪个物理节点
        for(int i =0; i < virtualhostnum; i++)
        {
            virtualhost_.emplace_back(ip + "#" + ::to_string(i), this);
        }
    }

    string GetIp() const
    {
        return ip_; 
    }

    const list<VirtualHost>& GetVirtualHosts() const
    {
        return virtualhost_;
    }
private:
    string ip_; // 物理机器的ip地址
    list<VirtualHost> virtualhost_; // 存储虚拟节点列表
};

// 一致性哈希
class ConsistentHash
{
public:
    // 在一致性哈希环上添加物理主机的虚拟节点
    void AddHost(PhysicalHost& host)
    {
        // 获取物理主机所有的虚拟节点列表
        auto list = host.GetVirtualHosts();
        for(auto host : list)
        {
            HashCircle_.insert(host);
        }
    }

    // 在一致性哈希环上删除物理主机的虚拟节点
    void DelHost(PhysicalHost& host)
    {
        // 获取物理主机所有的虚拟节点列表
        auto list = host.GetVirtualHosts();
        for(auto host : list)
        {
            auto it = HashCircle_.find(host);
            if(it != HashCircle_.end())
            {
                // 在一致性哈希环上删除所有物理主机对应的虚拟节点
                HashCircle_.erase(it);
            }
        }         
    }

    // 返回负载的真实物理主机的ip信息
    string GetHost(string clientip) const
    {
        uint md5 = getMD5Hash(clientip); 
        for(auto vhost : HashCircle_)
        {
            if(vhost.getMD5() > md5)
            {
                return vhost.getPhysicalHost()->GetIp();
            }
        }

        // 映射从0开始遇见的第一个虚拟节点
        return HashCircle_.begin()->getPhysicalHost()->GetIp();
    }

private:
    set<VirtualHost> HashCircle_; // 一致性哈希环
};

void ShowConsistentHash(ConsistentHash& chash);
// 测试
int main()
{
    PhysicalHost host1("10. 117.124.10",150);
    PhysicalHost host2("10.117.124.20",100);
    PhysicalHost host3("10.117.124.30",50);

    ConsistentHash chash;
    chash.AddHost(host1);
    chash.AddHost(host2);
    chash.AddHost(host3);
    
    ShowConsistentHash(chash);

    chash.DelHost(host1);

    ShowConsistentHash(chash);

    return 0;
}

void ShowConsistentHash(ConsistentHash& chash)
{
    list<string> iplists{"192.168.1.1",
    "192.168.1.2",
    "192.168.1.3",
    "192.168.1.4",
    "192.168.1.5",
    "192.168.1.6",
    "192.168.1.7"};
    
    map<string, list<string>> logmap;
    for(auto clientip : iplists)
    {
        string host = chash.GetHost(clientip);
        logmap[host].emplace_back(clientip);
    }
    
    for(auto pair : logmap)
    {
        cout << "物理主机的ip：" << pair.first << endl;
        cout << "客户端映射的数量：" << pair.second.size() << endl;
        for(auto ip : pair.second)
        {
            cout << ip << endl;
        }

        cout << "--------------------------" << endl;
    }
    cout << endl;    
}