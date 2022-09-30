#include<iostream>
#include<vector>
#include<cstdio>

using namespace std;

int extend_gcd(int a, int b, int &x, int &y ) {
    if ( b == 0 ) {
        x = 1;
        y = 0;
        return a;
    }

    int d = extend_gcd(b, a%b, x, y);
    int xd = y; int yd = x-a/b*y;
    x = xd; y = yd;
    return d;
}

int rev_mod( int a, int p ) {
    int x, y;
    extend_gcd(a,p, x, y);
    return ( ( x < 0 ) ? x+p : x );
}

int main()
{
    int p = 139;
    int x = 13;

    cout << rev_mod(x, p) << endl;
}
// int main()
// {
//     int n, p;

//     cin >> n >> p;
//     vector<int> inv(n+1, -1);

//     inv[1] = 1;
//     for ( int i = 2; i <= n; ++i ) {
//         inv[i] = p-(inv[p%i]*(p/i))%p;
//     }

//     for ( int i = 1; i <= n; ++i ) {
//         printf("inv[%d] = %d ( %d ) \n", i, inv[i], i*inv[i]%p);
//     }
// }