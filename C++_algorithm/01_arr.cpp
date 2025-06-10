#include<iostream>
#include<stdlib.h>
#include<ctime>
#include<cstring>
using namespace std;

// 整形数组，把偶数调整到数组的左边，把奇数调整到数组的右边
void AdjustArray(int arr[], int size)
{
    int *p = arr;
    int *q = arr + size -1;
    // while (p<q)
    // {
    //     if((*p & 0x1) == 0)
    //     {
    //         p++;
    //         continue;
    //     }
    //     if((*q & 0x1) == 1)
    //     {
    //         q--;
    //         continue;
    //     }

    //     int temp = *p;
    //     *p = *q;
    //     *q = temp;

    //     p++;
    //     q--;
    // }
    while (p<q)
    {
        while (p<q)
        {
            // p从左往右寻找奇数
            if((*p & 0x1) == 1)
            {
                break;
            }
            p++;
        }
        while (p<q)
        {
            // q从右往左寻找偶数
            if((*q & 0x1) == 0)
            {
                break;
            }
            q--;
        }
        if(p<q)
        {
            int temp = *p;
            *p = *q;
            *q = temp;

            p++;
            q--;
        }      
    }
}

int main()
{
    int arr[10] = {0};
    srand(time(0));
    for(int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
    {
        arr[i] = rand()%100;
    }

    for(int v:arr)
    {
        cout << v << " ";
    }
    cout << endl;

    AdjustArray(arr,sizeof(arr)/sizeof(arr[0]));

        for(int v:arr)
    {
        cout << v << " ";
    }
    cout << endl;
}


#if 0
// 逆序字符串
void Rerverse(char arr[], int size)
{
    char *p = arr;
    char *q = arr + size -1;
    while (p<q)
    {
        char ch = *p;
        *p = *q;
        *q = ch;
        p++;
        q--;
    }   
}
int main()
{
    char arr[] = "hello world";
    Rerverse(arr, strlen(arr));
    cout << arr << endl;
}
#endif

#if 0 
class Array
{
public:
    Array(int size=10):mCap(size),mNum(0)
    {
        mpArr = new int[mCap];
    }
    ~Array()
    {
        delete[] mpArr;
        mpArr = nullptr;
    }
    // 末尾增加元素
    void push_back(int val)
    {
        if(mCap==mNum) //如果末尾满了，需要扩容数组
        {
            expand(2*mCap);
        }
        mpArr[mNum] = val;
        mNum++;
    }
    // 末尾删除元素
    void pop_bask()
    {
        if(mNum==0)
        {
            return;
        }
        mNum--;
    }
    // 增加元素
    void insert(int pos,int val)
    {
        if(pos>mNum || pos < 0)
        {
            return;
        }
        if(mCap==mNum) //如果末尾满了，需要扩容数组
        {
            expand(2*mCap);
        }
        for(int i=mNum-1;i>=pos;i--)
        {
            mpArr[i+1] = mpArr[i];
        }

        mpArr[pos] = val;
        mNum++;

    }
    // 按元素删除
    void erase(int pos)
    {
       if(pos>mNum || pos < 0)
        {
            return;
        }
        for(int i=pos+1;i<mNum;i++)
        {
            mpArr[i-1] = mpArr[i];
        }
        mNum--;
    }

    // 元素查询
    int find(int val)
    {
        for(int i=0;i<mNum;i++)
        {
            if(val == mpArr[i])
            {
                return i;
            }
        }
        return -1;
    }

    void show()
    {
        for(int i=0;i<mNum;i++)
        {
            cout << mpArr[i] << " ";
        } 
        cout << endl; 
    }

private:
    int expand(int size)
    {
        int *p = new int[size];
        memcpy(p,mpArr,sizeof(int)*mCap);
        delete[] mpArr;

        mpArr = p;
        mCap = size;

    }   
    int *mpArr; // 数据指针
    int mCap; // 数组容量
    int mNum; //数组有效个数

};

int main()
{
    Array arr;
    srand(time(0));
    for(int i=0;i<10;i++)
    {
        arr.push_back(rand()%100);
    }

    arr.show();

    arr.pop_bask();
    arr.show();  

    arr.insert(1,100);
    arr.show();    
    
    arr.erase(1);
    arr.show();  

    return 0;
}
#endif

