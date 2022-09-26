#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

template<class T>
class SegTree {
  T (*ope) ( T, T );
  T zele;
  int ln;
  vector<T> tree;
  vector<T> delay;

  void build() {
    for ( int i = ln-2; i >= 0; --i ) {
      tree[i] = (*ope)(tree[i*2+1], tree[i*2+2]);
    }
  }

public:

  SegTree( T (*ope1) (T,T), T zele1, const vector<T>& v) : ope(ope1), zele(zele1) {

    this->ln = 1;
    while( ln < v.size() ) this->ln = ln<<1;
    tree = vector<T>(ln*2-1, zele);
    for ( int i = 0; i < v.size(); ++i ) tree[i+ln-1] = v[i];
    if ( ln > 1 ) build();
  }

  SegTree ( T (*ope1) (T,T), T zele1, int n ) : SegTree( ope1, zele1, vector<T>(n, zele1)){
  }

  void update(int i, T v ) { // 0-origin
    i = i+ln-1;
    tree[i] = v;
    while( i > 0 ) {
      i = (i-1)/2;
      tree[i] = (*ope)(tree[i*2+1], tree[i*2+2]);
    }
  }

  void add( int i, T v ) { //+演算子必須
    update( i, tree[i+ln-1]+v);
  }

  T find(int l, int r, int i, int nl, int nr ) { //半開区間[l-r)の探索 0-origin
    if ( nl >= l && nr <= r ) return tree[i];
    if ( nl >= r || nr <= l ) return zele;

    int mid =  (nl+nr)/2;
    return (*ope)( find(l,r,i*2+1,nl,mid), find(l,r,i*2+2,mid,nr));
  }

  T find(int l, int r) { return find(l,r,0,0,ln); }

  void print() {
    cout << "ln = " << ln << endl;
    cout << "Print: ";
    for ( auto v : tree ) cout << v << " ";
    cout << endl;
  }
};

int main()
{
  int n,q;
  int MAXV = (1LL<<31)-1;
  cin >> n >> q;

  SegTree<int> rmq( [](int x, int y){return min(x,y);}, MAXV, n);

  while(q--) {
    int cmd, x, y;
    cin >> cmd >> x >> y;
    if ( cmd ) cout << rmq.find(x,y+1) << endl;
    else rmq.update(x,y);
  }
}
