#include <iostream>
using namespace std;
#include"time.h"
#include<vector>
#include<list>
#include<algorithm>

class HashTable
{
public:
    HashTable(int size = primes_[0], double LoadFactor = 0.75)
        : UseBucketNum(0)
        , LoadFactor_(LoadFactor)
        , primeIdx(0)
        {
            // 把用户传进的size调整到最近的比较大的素数上
            if(size != primes_[0])
            {
                for(; primeIdx < PRIME_SIZE; primeIdx++)
                {
                    if(primes_[primeIdx] >= size)
                    {
                        break;
                    }
                }
                
                // 用户传入的size过大，已经超过最后一个素数，调整到最后一个素数
                if(primeIdx == PRIME_SIZE)
                {
                    primeIdx--;
                }
            }

            table_.resize(primes_[primeIdx]);
        }

public:
    // 增加元素
    void insert(int key)
    {
        double factor = UseBucketNum * 1.0 / table_.size();
        cout << "factor: " << factor << endl;
        if(factor > LoadFactor_)
        {
            expand();
        }

        int idx = key % table_.size(); // O(1)
        if(table_[idx].empty())
        {
            UseBucketNum++;
            table_[idx].emplace_front(key);
        }
        else
        {
            // 使用全局的:: find 泛型算法，而不是调用自己的成员方法find
            // 去重
            auto it = ::find(table_[idx].begin(),table_[idx].end(),key); // O(n)
            if(it == table_[idx].end())
            {
                // 不存在
                table_[idx].emplace_front(key);
            }
        }
    }

    // 删除元素
    void erase(int key)
    {
        int idx = key % table_.size(); // O(1)
        // 如果链表节点过长：如果散列结果比较集中（散列函数有问题！！！)
        // 如果散列结果比较离散，链表长度一般不会过长，因为有装载因子
        auto it = ::find(table_[idx].begin(),table_[idx].end(),key); // O(n)
        if(it != table_[idx].end())
        {
            // 找到了
            table_[idx].erase(it);
            if(table_[idx].empty())
            {
                // 桶为空
                UseBucketNum--;
            }   
        }    
    }
    // 搜索
    bool find(int key)
    {
        int idx = key % table_.size();
        auto it = ::find(table_[idx].begin(),table_[idx].end(),key); 
        return it != table_[idx].end();         
    }

private:
    void expand()
    {
        ++primeIdx;
        if(primeIdx == PRIME_SIZE)
        {
            throw "HashTable is too large, can not expand anymore !";
        }

        UseBucketNum = 0;

        vector<list<int>> oldtable;
        // swap会不会效率很低？？？
        // 交换了两个容器的成员变量
        table_.swap(oldtable);
        table_.resize(primes_[primeIdx]);
        
        for(auto list : oldtable)
        {
            for(auto key : list)
            {
                int idx = key % table_.size();
                if(table_[idx].empty())
                {
                    UseBucketNum++;
                }
                table_[idx].emplace_front(key);
            }
        }
    }

private:
    vector<list<int>> table_; // 指向动态开辟的哈希表
    int UseBucketNum; // 已经使用的桶的个数
    double LoadFactor_; // 哈希表的装载因子

    static const int PRIME_SIZE = 10; // 素数表的大小
    static int primes_[PRIME_SIZE]; // 素数表
    int primeIdx; // 当前使用的素数下标

};

int HashTable::primes_[PRIME_SIZE] = {3,7,23,47,97,251,443,991,1471,42773};

int main()
{
    HashTable ht;
    ht.insert(11);
    ht.insert(22);
    ht.insert(33);
    ht.insert(44);
    ht.insert(55);

    cout << ht.find(22) << endl;
    ht.erase(22);
    cout << ht.find(22) << endl;
    return 0;
}
