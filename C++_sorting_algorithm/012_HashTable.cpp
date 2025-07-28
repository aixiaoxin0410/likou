#include <iostream>
using namespace std;
#include"time.h"
#include<vector>


enum State
{
    STATE_UNUSE, // 从未使用过的桶
    STATE_USE, // 正在使用的桶
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
    srand(time(0));
    int arr[10];
    for(int i = 0 ;i < 10; i ++)
    {
        arr[i] = rand()% 100;
        cout << arr[i] << " ";
    }
    cout << endl;

    arr[9] = -123;
    arr[6] = -38;

    // RadixSort(arr, sizeof(arr)/sizeof(arr[0]));

    for(int v : arr)
    {
        cout << v << " ";
    }
    cout << endl;
    return 0;
}
