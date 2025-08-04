#include <iostream>
using namespace std;
#include"time.h"
#include<vector>


enum State
{
    STATE_UNUSE, // 从未使用过的桶
    STATE_USING, // 正在使用的桶
    STATE_DEL, // 元素被删掉的桶
};

struct Bucket
{
    Bucket(int key =0, State state = STATE_UNUSE)
        : key_(key)
        , state_(state)
        {};
    int key_; // 存储的数据
    State state_; // 桶的当前状态
};

class HashTable
{
public:
    HashTable(int size = primes_[0], double LoadFactor = 0.75)
        : UseBacketNum(0)
        , LoadFactor_(LoadFactor)
        , primeIdx(0)
        {
            // 把用户传进的size调整到最近的比较大的素数上
            if(size != primes_[0])
            {
                for(; primeIdx < PRIME_SIZE; primeIdx++)
                {
                    if(primes_[primeIdx] > size)
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

            TableSize = primes_[primeIdx];
            table_ = new Bucket[TableSize];

        }

        ~HashTable()
        {
            delete[] table_;
            table_ = nullptr;
        }

    // 插入元素
    bool insert(int key)
    {
        double factor = UseBacketNum * 1.0 / TableSize;
        cout << "factor: " << factor << endl;

        // 考虑扩容
        if(factor > LoadFactor_)
        {
            expand();
        }

        int idx = key % TableSize;

        int i = idx;
        do
        {
            if(table_[i].state_ != STATE_USING)
            {
                table_[i].key_ = key;
                table_[i].state_ = STATE_USING;
                UseBacketNum++;
                return true;
            }
            i = (i + 1) % TableSize;
        } while (i != idx);
        
        return false;
    }
    
    // 删除元素
    bool erase(int key)
    {
        int idx = key % TableSize;

        int i = idx;
        do
        {
            if(table_[i].key_ == key && table_[i].state_ == STATE_USING)
            {
                table_[i].state_ = STATE_DEL;
                UseBacketNum--;
            }
            i = (i + 1) % TableSize;
        } while (table_[i].state_ != STATE_UNUSE && i != idx);
        
        return true;      
    }

    // 查询
    bool find(int key)
    {
        int idx = key % TableSize;

        int i = idx;
        do
        {
            if(table_[i].key_ == key && table_[i].state_ == STATE_USING)
            {
                return true;
            }
            i = (i + 1) % TableSize;
        } while (table_[i].state_ != STATE_UNUSE && i != idx);
        
        return false;            
    }

private:
    void expand()
    {
        ++primeIdx;
        if(primeIdx == PRIME_SIZE)
        {
            throw "HashTable is too large, can not expand anymore !";
        }

        Bucket* newtable_ = new Bucket[primes_[primeIdx]];

        // 旧表有效的数据，重新哈希放到扩容后的新表
        for(int i = 0; i < TableSize; i++)
        {
            if(table_[i].state_ == STATE_USING)
            {
                int idx = table_[i].key_ % primes_[primeIdx];

                int k = idx;
                do
                {
                    if(newtable_[k].state_ != STATE_USING)
                    {
                        newtable_[k].state_ = STATE_USING;
                        newtable_[k].key_ = table_[i].key_;
                        break;
                    }
                    k = (k + 1) % primes_[primeIdx];
                } while (k != idx);   
            }   
        }

        delete[] table_;
        table_ = newtable_;
        TableSize = primes_[primeIdx];
    }

private:
    Bucket * table_; // 指向动态开辟的哈希表
    int TableSize; // 哈希表当前的长度
    int UseBacketNum; // 已经使用的桶的个数
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

    cout << ht.find(55) << endl;
    ht.erase(55);
    cout << ht.find(55) << endl;
    return 0;
}
