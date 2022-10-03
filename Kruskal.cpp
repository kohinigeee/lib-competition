#include<iostream>
#include<vector>
#include<algorithm>
#include<string>


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


using kruskal_t = long long;

class Kruskal { //無向グラフ・連結　前提

    public:
    class Edge {
        public:
        kruskal_t t1, t2, c;

        Edge(kruskal_t t1, kruskal_t t2, kruskal_t c) : t1(t1), t2(t2), c(c) {}
    };

    private:
    vector<Edge> edges;
    vector<string> names;
    kruskal_t n;

    kruskal_t minsum;
    vector<Edge> ans;

    void cal() {

        UnionFind uf(n);
        minsum = 0;

        sort(edges.begin(), edges.end(), [](const Edge& e1, const Edge& e2 ){ return e1.c < e2.c; });

        for ( auto& e : edges ) {
            if ( !uf.same(e.t1, e.t2) ) {
                minsum += e.c;
                uf.unite(e.t1, e.t2);
                ans.push_back(e);
            }
        }
    }


    public:

        Kruskal(kruskal_t n, vector<Edge>& edges, vector<string> names = (vector<string>()) ) : n(n), edges(edges), names(names) {
            if ( this->names.size() == 0 ) {
              this->names = vector<string>(n);
              for ( int i = 0; i < n; ++i ) this->names[i] = to_string(i);
            }
            cal();
        }

        kruskal_t getCost() {
            return minsum;
        }

        void print() {
            for ( int i = 0; i < ans.size(); ++i ) {
                Edge& e = ans[i];
                string s = "[" + to_string(i) + "]";
                s += " (" + names[e.t1] + " - " + names[e.t2] + ") cost:" + to_string(e.c);
                cout << s << endl;
            }
            cout << "total cost: " << minsum << endl;
        }

};

int main()
{
    vector<Kruskal::Edge> edges;
    vector<string> names;
    int n, m;

    cin >> n >> m;
    for ( int i = 0; i < m; ++i ) {
      int s, t, c; cin >> s >> t >> c;
      edges.push_back(Kruskal::Edge(s, t, c));
    }

    names = vector<string>(n);
    for ( int i = 0; i < n; ++i ) cin >> names[i];

    Kruskal kru(n, edges, names);
    cout << endl;
    kru.print();
}

/* 入力例　グラフ1
5 10
0 1 4
0 2 9
0 3 6
0 4 10
1 2 8
1 3 7
1 4 5
2 3 3
2 4 1
3 4 2
s
a
b
c
d
e

グラフ2
6 15
0 1 14
0 2 6
0 3 5
0 4 7
0 5 12
1 2 10
1 3 15
1 4 4
1 5 2
2 3 1
2 4 13
2 5 9
3 4 11
3 5 8
4 5 3
s
a
b
c
d
e
*/