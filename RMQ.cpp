#include<iostream>
#include<vector>
#include<algorithm>

#define MAXV ((1LL<<31)-1)

using namespace std;
using data = long long;

class RMQ {
  vector<data> tree;
  int ln;

  void build() {
    for ( int i = ln-2; i >= 0; --i ) {
      tree[i] = min(tree[i*2+1], tree[i*2+2]);
    }
  }

public:

  RMQ( int n ) : RMQ(vector<data> (n, MAXV)) { }

  RMQ( const vector<data>& vec ) {
    ln = 1;
    while( ln < vec.size() ) ln = ln<<1;
    tree = vector<data>(ln*2-1, MAXV);
    for ( int i = 0; i < vec.size(); ++i ) tree[i+ln-1] = vec[i];
    build();
  }

  void update(int i, data x ) {
    int j = i+ln-1;
    if ( j >= tree.size() ) return;
    tree[j] = x;
    while( j > 0 ) {
      j = (j-1)/2;
      tree[j] = min(tree[j*2+1], tree[j*2+2]);
    }
  }

  data find(int l, int r, int i, int nl, int nr) { //半開区間[l, r)
    if ( nl >= l && nr <= r ) return tree[i];
    if ( nr <= l || nl >= r ) return MAXV;

    int mid = (nl+nr)/2;
    return min(find(l,r,i*2+1,nl,mid), find(l,r,i*2+2,mid,nr));
  }

  data find(int l, int r ) { return find(l, r, 0, 0, ln); }

};

int main()
{
  int n, q;
  cin >> n >> q;
  RMQ r = RMQ(n);

  while(q--) {
    int cmd, x, y;
    cin >> cmd >> x >> y;
    if ( cmd ) {
      cout << r.find(x,y+1) << endl;
    } else {
      r.update(x, y);
    }
  }
}
