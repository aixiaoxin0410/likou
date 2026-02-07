#include <iostream>
using namespace std;

// BF算法
int BF(string s, string t)
{
    int i = 0;
    int j = 0;
    while(i < s.size() && j < t.size())
    {
        if(s[i] == t[j])
        {
            i++;
            j++;
        }
        else
        {
            i = i - j + 1; // 复位 i 指向之前开始匹配字符的下一个字符
            j = 0;
        }
    }
    if(j == t.size())
    {
        // 找到了
        return i - j;
    }
    else
    {
        return -1;
    }
}

int main()
{
    string s = "ABCDCABDEFG";
    string t = "ABX";

    int pos = BF(s,t);
    cout << "pos: " << pos << endl;
    return 0;
}