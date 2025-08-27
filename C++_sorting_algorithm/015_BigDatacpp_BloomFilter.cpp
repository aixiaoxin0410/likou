#include <iostream>
using namespace std;
#include "StringHash.h"
#include <vector>

// 布隆过滤器
class BloomFilter
{
public:
    BloomFilter(int bitsize = 1471)
        : Bitsize(bitsize)
        {
            BitMap.resize(Bitsize / 32 + 1);
        }

public:
    // 添加元素 O(1)
    void setBit(const char* str)
    {
        // 计算 k 组哈希函数的值
        int idx1 = yzz::BKDRHash(str) % Bitsize;
        int idx2 = yzz::APHash(str) % Bitsize;
        int idx3 = yzz::RSHash(str) % Bitsize;

        // 把相应的idx1 idx2 idx3 这几个位全部置1
        int index = 0;
        int offset = 0;

        index = idx1 / 32;
        offset = idx1 % 32;
        BitMap[index] |= (1 << offset); 

        index = idx2 / 32;
        offset = idx2 % 32;
        BitMap[index] |= (1 << offset); 

        index = idx3 / 32;
        offset = idx3 % 32;
        BitMap[index] |= (1 << offset); 

    }

    // 查询元素 O(1)
    bool getBit(const char* str)
    {
        // 计算 k 组哈希函数的值
        int idx1 = yzz::BKDRHash(str) % Bitsize;
        int idx2 = yzz::APHash(str) % Bitsize;
        int idx3 = yzz::RSHash(str) % Bitsize;

        int index = 0;
        int offset = 0;

        index = idx1 / 32;
        offset = idx1 % 32;
        if((BitMap[index] & (1 << offset)) == 0)
        {
            return false;
        }

        index = idx2 / 32;
        offset = idx2 % 32;
        if((BitMap[index] & (1 << offset)) == 0)
        {
            return false;
        }

        index = idx3 / 32;
        offset = idx3 % 32;
        if((BitMap[index] & (1 << offset)) == 0)
        {
            return false;
        }

        return true;
    }

private:
    int Bitsize; // 位图的长度
    vector<int> BitMap; //位图数组
};


// URL黑名单
class BlackList
{
public:
    void add(string url)
    {
        blacklist.setBit(url.c_str());
    }

    bool query(string url)
    {
        return blacklist.getBit(url.c_str());
    }

private:
    BloomFilter blacklist;
};

int main()
{
    BlackList BL;
    BL.add("www.111.com");
    BL.add("www.222.com");
    BL.add("www.333.com");
    BL.add("www.444.com");

    string URL = "www.1.com";
    cout << BL.query(URL) << endl;    
    return 0;
}