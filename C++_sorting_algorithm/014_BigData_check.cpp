#include <iostream>
using namespace std;
#include<ctime>
#include<vector>
#include<unordered_map>
#include<unordered_set>
#include<memory>

#if 0 
int main()
{
    srand(time(0));
    vector<int> vec;

    for(int i = 0; i< 10000;i++)
    {
        vec.push_back(rand()% 10000);
    }

    // unordered_set<int> us;
    // for(auto key : vec )
    // {
    //     auto it = us.find(key);
    //     if(it == us.end())
    //     {
    //         us.insert(key);
    //     }
    //     else
    //     {
    //         cout << "key: " << key << endl;
    //         break;
    //     }
    // }

    unordered_map<int, int> m1;
    for(auto key : vec)
    {
        auto it = m1.find(key); // O(1)
        if(it == m1.end())
        {
            m1.emplace(key,1); // O(1)
        }
        else
        {
            it->second+=1;
        }
    }

    for(auto pair : m1)
    {
        if(pair.second > 3)
        {
            cout << "value: " << pair.first << " " << "cnt: " << 
            pair.second << endl;
        }
    }

    unordered_set<int> s1;
    for(auto key : vec)
    {
        s1.emplace(key);
    }
    return 0;
}


int main()
{
    string src = "aapoo jwtpja";
    unordered_map<char, int> um;
    for(auto ch : src)
    {
        auto it = um.find(ch);
        if(it == um.end())
        {
            um.emplace(ch,1);
        }
        else
        {
            it->second+= 1;
        }
    }

    for(auto ch : src)
    {
        if(um[ch] == 1)
        {
            cout << "第一个没有重复出现过的字符是：" << ch << endl;
            return 0;
        }
    }

    cout << "所有字符都重复出现过！" << endl;
    return 0;
}

# endif

// 位图算法
int main()
{
    vector<int> vec{12, 78, 90, 123, 8 ,9, 90, 12};
    int max = vec[0];
    for(int i = 1; i < vec.size(); i++)
    {
        if(vec[i] > max)
        {
            max = vec[i];
        }
    }

    // cout << max << endl;
    int *bitmap = new int[max / 32 + 1](); // 初始化
    unique_ptr<int> pre(bitmap);

    // 找第一个重复出现的数字
    for(auto key : vec)
    {
        int index = key / 32;
        int offset = key % 32;
        if(0 == ( bitmap[index] & (1 << offset) ) )
        {
            bitmap[index] |= (1 << offset);
        }
        else
        {
            // cout << key << " 是第一个重复出现的数字" << endl;
            // return 0;
            cout << key << " 重复出现过" << endl; 
        }
    }
}