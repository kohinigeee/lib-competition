#include<iostream>
#include<vector>
#include<algorithm>

#define MINV -1

using namespace std;
using ll = long long;

class RMQ {
  vector<ll> tree;
  int ln;

  void build() {
    for ( int i = ln-2; i >= 0; --i ) {
      tree[i] = max(tree[i*2+1], tree[i*2+2]);
    }
  }

public:

  RMQ( int n ) : RMQ(vector<ll> (n, MINV)) { }

  RMQ( const vector<ll>& vec ) {
    ln = 1;
    while( ln < vec.size() ) ln = ln<<1;
    tree = vector<ll>(ln*2-1, MINV);
    for ( int i = 0; i < vec.size(); ++i ) tree[i+ln-1] = vec[i];
    if ( ln > 1 ) build();
  }

  void update(int i, ll x ) {
    int j = i+ln-1;
    if ( j >= tree.size() ) return;
    tree[j] = x;
    while( j > 0 ) {
      j = (j-1)/2;
      tree[j] = max(tree[j*2+1], tree[j*2+2]);
    }
  }

  ll find(int l, int r, int i, int nl, int nr) { //半開区間[l, r)
    if ( nl >= l && nr <= r ) return tree[i];
    if ( nr <= l || nl >= r ) return MINV;

    int mid = (nl+nr)/2;
    return max(find(l,r,i*2+1,nl,mid), find(l,r,i*2+2,mid,nr));
  }

  ll find(int l, int r ) { return find(l, r, 0, 0, ln); }
};

using vl = vector<ll>;

int main()
{
  vector<vl> dp;
  vl l, r, v;
  int n, w;

  cin >> w >> n;
  l = vl(n); r = vl(n); v = vl(n);
  dp = vector<vl>(n, vl(w+1, MINV));

  for ( int i = 0; i < n; ++i ) cin >> l[i] >> r[i] >> v[i];
  for ( int i = l[0]; i <= r[0]; ++i ) dp[0][i] = v[0];
  dp[0][0] = 0;

  for ( int i = 1; i < n; ++i ) {
    RMQ rm( dp[i-1] );
    for ( int j = 0; j <= w; ++j ) {
      dp[i][j] = dp[i-1][j];
      if ( j-l[i] >= 0 ) {
        ll tmp = rm.find( max(0LL, j-r[i]), j-l[i]+1);
        if ( tmp != MINV ) dp[i][j] = max(dp[i][j], tmp+v[i]);
      }
    }
  }

  cout << dp[n-1][w] << endl;

}
