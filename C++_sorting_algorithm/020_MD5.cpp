#include <iostream>
using namespace std;
#include "md5.h"

int main()
{
    cout << MD5("hello world") << endl;
    cout << MD5("110") << endl;
    cout << MD5("192.168.1.130#0") << endl;
    cout << getMD5("520") << endl;

    return 0;
}
