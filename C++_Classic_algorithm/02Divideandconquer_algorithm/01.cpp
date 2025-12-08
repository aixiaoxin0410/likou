#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// 分治算法思想：二分搜索
bool BinarySearch(vector<int>&vec,int i , int j, int number)
{
    if(i > j)
    {
        return false; // 元素不存在
    }
    int mid = (i + j) / 2;
    if(vec[mid] == number) // 子问题[i,j]解是已知的了
    {
        return true;
    }
    else if(vec[mid] > number) // 在[i,mid - 1]子规模问题中
    {
        return BinarySearch(vec,i,mid-1,number);
    }
    else // 在[mid + 1, j]子规模问题中
    {
        return BinarySearch(vec,mid+1,j,number);
    }
}

int main()
{
    vector<int> vec;
    for(int i = 0;i<10;i++)
    {
        vec.push_back(rand()%100);
    }
    sort(vec.begin(),vec.end());
    for(int v:vec)
    {
        cout << v << " ";
    }
    cout << endl;

    bool result = BinarySearch(vec,0,vec.size()-1,1);
    cout << "result: " << result << endl; 
    return 0;
}