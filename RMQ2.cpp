#include<iostream>
#include<vector>
#include<algorithm>

#define MAXV ((1LL<<31)-1)
#define NULLV (-1)

using namespace std;
using data = long long;

class RMQ {
  vector<data> tree;
  vector<data> delay;
  int ln;

  void build() {
    for ( int i = ln-2; i >= 0; --i ) {
      tree[i] = min(tree[i*2+1], tree[i*2+2]);
    }
  }

  void eval(int i ) {
    if ( delay[i] == NULLV ) return;
    tree[i] = delay[i];
    delay[i] = NULLV;
    if ( i < ln-1 ) {
      delay[i*2+1] = tree[i];
      delay[i*2+2] = tree[i];
    }
  }

public:

  RMQ( int n ) : RMQ(vector<data> (n, MAXV)) { }

  RMQ( const vector<data>& vec ) {
    ln = 1;
    while( ln < vec.size() ) ln = ln<<1;
    tree = vector<data>(ln*2-1, MAXV);
    delay = vector<data>(ln*2-1, NULLV);
    for ( int i = 0; i < vec.size(); ++i ) tree[i+ln-1] = vec[i];
    build();
  }

  // void update(int i, data x ) {
  //   int j = i+ln-1;
  //   if ( j >= tree.size() ) return;
  //   tree[j] = x;
  //   while( j > 0 ) {
  //     j = (j-1)/2;
  //     tree[j] = min(tree[j*2+1], tree[j*2+2]);
  //   }
  // }

  void update(int l, int r, data x, int i, int nl, int nr ) {
    eval(i);
    if ( nl >= l && nr <= r ) { delay[i] = x; eval(i); return; }
    if ( nr <= l || nl >= r ) return;

    int mid = (nl+nr)/2;

    update(l, r, x, i*2+1, nl, mid);
    update(l, r, x, i*2+2, mid, nr);
    tree[i] = min(tree[i*2+1], tree[i*2+2]);
  }

  void update(int l, int r, data x ) { update(l,r,x,0,0,ln); } //半開区間[l, r)

  data find(int l, int r, int i, int nl, int nr) { //半開区間[l, r)
    eval(i);

    if ( nl >= l && nr <= r ) return tree[i];
    if ( nr <= l || nl >= r ) return MAXV;

    int mid = (nl+nr)/2;
    return min(find(l,r,i*2+1,nl,mid), find(l,r,i*2+2,mid,nr));
  }

  data find(int l, int r ) { return find(l, r, 0, 0, ln); }

};

int main()
{
  int n = 10;
  RMQ r = RMQ(n);

  r.update(0, 4, 3);
  cout << r.find(0, 4) << endl;
  r.update(2, 6, 10);
  cout << r.find(3,4) << endl;
}
