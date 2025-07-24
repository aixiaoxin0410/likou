#include <iostream>
using namespace std;
#include"time.h"
#include<vector>

// 基数排序（只能处理 >= 0 的整数），没法处理负数
// 思路：桶的个数不再是10个，而是20个，0-19

// 时间复杂度：O(nd)
// 空间复杂度：O(n)
// 稳定
void RadixSort(int arr[], int size)
{
    int maxdata = arr[0];
    for(int i = 0; i < size; i++)
    {
        if(abs(arr[i]) > maxdata)
        {
            maxdata = abs(arr[i]);
        }
    }
    int len = to_string(maxdata).size();

    vector< vector<int> > vearr;
    int mod = 10;
    int dev = 1;   

    for(int i =0 ;i< len;mod*=10, dev*=10,i++) // O(d) d：数据的长度
    {
        vearr.resize(20); // 20个桶，为了能处理负数 -9 —— +9
        for(int j =0;j<size;j++) // O(n)
        {
            // 得到当前元素第i个位置的数字
            int index = arr[j] % mod / dev + 10;
            vearr[index].push_back(arr[j]);
        }
        
        // 依次遍历所有的桶，把元素拷贝回原始的数组中
        int idx = 0;
        for(auto v:vearr) // O(20)
        {
            for(auto i:v) // O(n) O(20)* O(n) = O(n)
            {
                arr[idx++] = i;
            }
        }

        vearr.clear();
    }
}

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

    RadixSort(arr, sizeof(arr)/sizeof(arr[0]));

    for(int v : arr)
    {
        cout << v << " ";
    }
    cout << endl;
    return 0;
}
