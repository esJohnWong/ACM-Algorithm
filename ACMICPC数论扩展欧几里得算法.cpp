#include<iostream>

using namespace std;

int extendGcd(int n , int m , int &x , int &y)
{
    if(m == 0)
    {
        x = 1 , y = 0;
        return n;
    }
    int tmp = extendGcd(m , n%m , x , y);
    int tmp1 = x;
    x = y;
    y = tmp1 - n/m*y;
    return tmp;
}

int main()
{
    int n , m;
    while(cin>>n>>m)
    {
        int x , y , d;
        d = extendGcd(n , m , x , y);
        cout<<d<<" "<<x<<" "<<y<<endl;
    }
    return 0;
}
