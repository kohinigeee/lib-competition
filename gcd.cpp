#include<iostream>

using namespace std;

long long gcd ( long long a, long long b ) {
    long long r;

    while ( r = a%b ) {
        a = b;
        b = r;
    }
    return b;
}

int main()
{
   long long x,y;

   cin >> x >> y;
   cout << gcd(x,y) << endl; 
}