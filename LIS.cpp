//単調増加部分列(Longest Increasing Subsequence)のサイズを求める
#include<iostream>
#include<vector>
#include<algorithm>

#define INF 1000000007

using namespace std;

using ll = long long;

ll LIS(vector<ll>& a, ll inf ) {
    vector<ll> dp( a.size(), inf);
    ll dp_size = 0;
    for ( int i = 0; i < a.size(); ++i ) {
        auto it  = lower_bound(dp.begin(), dp.end(), a[i]); //広義の単調増加なら、upper_boundを使用
        if ( *it == INF ) ++dp_size;
        *it = a[i];
    }

    return dp_size;
}

int main()
{
    vector<ll> a;
    vector<ll> dp;
    int n;

    cin >> n;
    a = vector<ll>(n, 0);

    for ( int i = 0; i < n; ++i ) cin >> a[i];
    cout << LIS(a, INF) << endl;
}