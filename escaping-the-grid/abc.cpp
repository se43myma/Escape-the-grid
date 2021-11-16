#include <iostream>
#include <memory>

using namespace std;

int main()
{
    int c=5;
    int* b;
    *b=c;
    int* a=new int[5];
    memcpy(a,b,5);
    for(int i=0;i<5;i++)
    {
        cout<<a[i]<<" ";
    }
}