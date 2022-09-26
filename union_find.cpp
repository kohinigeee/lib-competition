#include<iostream>
#include<vector>

using namespace std;

class UnionFind {
  vector<int> p;
  vector<int> size;

  int root( int x ) {
    if ( x == p[x] ) return x;
    return p[x] = root(p[x]);
  }

public:

  UnionFind(int n ) {
    p = vector<int>(n);
    size = vector<int>(n, 1);
    for ( int i = 0; i < n; ++i ) p[i] = i;
  }

  bool same( int x, int y ) {
    return root(x) == root(y);
  }

  void unite( int x, int y ) {
    if ( same(x,y) ) return;
    x = root(x); y = root(y);
    size[x] += size[y];
    p[y] = x;
  }

  int get_size( int x ) {
    return size[root(x)];
  }
};

void gs(UnionFind& uf, int x ) {
  cout << "size[" << x << "] = " << uf.get_size(x) << endl;
}

int main() {

  int n = 10;

  UnionFind uf(n);

  gs(uf, 2);
  uf.unite(2, 5);
  uf.unite(4,5);
  gs(uf, 2);
  uf.unite(1,0);
  gs(uf, 1);
  uf.unite(0, 4);
  gs(uf, 1);
  
}
