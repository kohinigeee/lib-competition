#include<iostream>
#include<vector>
#include<queue>
#include<utility>

#define WHITE 0
#define BLACK 1
#define INF -1

using namespace std;

using vp = vector<pair<int,int>>;
using vvp = vector<vp>;
using ll = long long;

vector<ll> dijkstra( int s, vvp& g ) {
  vector<ll> d( g.size(), INF);
  priority_queue<pair<int,int>, vp, greater<pair<int,int>>> q;

  q.push(make_pair(0, s));
  d[s] = 0;

  while( !q.empty() ) {
    int v = q.top().second, dv = q.top().first; q.pop();
    if ( d[v] != dv ) continue;

    for ( pair<int,int> p : g[v] ) {
      int to = p.first, c = p.second;
      if ( d[to] == INF ||  d[v] + c < d[to] ) {
        d[to] = d[v]+c;
        q.push(make_pair(d[to], to));
      }
    }
  }
  return d;
}

int main()
{
  int v, e, r;
  vvp g;

  cin >> v >> e >> r;
  g = vvp( v, vp());
  while(e--) {
    int s, t, d;
    cin >> s >> t >> d;
    g[s].push_back(make_pair(t,d));
  }

  vector<ll> ans = dijkstra(r, g);
  for ( auto i : ans ) {
    if ( i == INF ) cout << "INF" << endl;
    else cout << i << endl;
  }
}
