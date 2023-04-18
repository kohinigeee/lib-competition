#include<iostream>
#include<vector>

using namespace std;

using ll = long long;

ll kousoku2(ll x, int y, ll p ) {
    ll ans = 1;
    ll base = x;
    while( y > 0 ) {
        if ( y&1 ) {
            ans *= base;
            ans %= p;
        }
        base *= base;
        base %= p;
        y = y >> 1;
    }
    return ans;
}

ll rev_mod(ll x, ll p ) {
    return kousoku2(x, p-2, p);
}

int main()
{
    const ll MOD = 998244353;
    // cout << rev_mod(5, MOD) << endl;
    // cout << kousoku2(3, 2) << endl;
    // cout << kousoku2(3, 5) << endl;

    ll y = 2;
    ll x = 25;

    cout << y*rev_mod(x, MOD)%MOD << endl;
}