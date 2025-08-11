#include <iostream>
using namespace std;
#include<ctime>
#include<vector>
#include<unordered_map>
#include<unordered_set>

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
# endif

int main()
{
    string src = "aapoojwtpja";
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
