#include<iostream>
#include<cmath>
#include<vector>
using namespace std;

/* 
挑选数字:有一组整数，请挑选出一组数字，让他们的和等于指定的值,存在解打印，不存在打印。
*/

int arr[] = {4, 8, 12, 16, 7, 9, 3, 3};
const int length = sizeof(arr)/sizeof(arr[0]);
int number = 18; 
vector<int>vec; // 存放选择的数字

void func(int i,int number)
{
    if(number == 0)
    {
        for(int v:vec)
        {
            cout << v << " ";
        }
        cout << endl;   
    }
    else
    {
        // 以当前节点开始，把剩余元素的孩子节点生成
        for(int k = i; k<length;++k)
        {
            if(number >= arr[k]) // 剩余的元素小于number（待组成的元素值）
            {
                vec.push_back(arr[k]);
                // 初始元素组有重复数字：
                // 当前层遍历到下一层的时候 arr[k] != arr[k-1]

                // 不允许重复选择元素
                func(k+1,number - arr[k]); // 遍历孩子节点，表示arr[k]的孩子节点

                // 允许重复选择元素
                // func(k,number - arr[k]); 
                vec.pop_back();
            }

        }
    }
}
int main()
{
    func(0,number);
    return 0;
}