#include<iostream>
#include<stdlib.h>
#include<ctime>
using namespace std;


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