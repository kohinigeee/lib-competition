#include<iostream>
#include<vector>
#include<utility>
#include<algorithm>

using namespace std;

int dfs(int x, int no, const vector<vector<int>>& g, vector<pair<int,int>>& ord) {
  ord[x].first = 0;
  for ( auto t : g[x] ) {
    if ( ord[t].first == -1 ) {
      no = dfs(t, no, g, ord);
    }
  }
  ord[x].first = no;
  return no+1;
}

void dfs2(int x, const vector<vector<int>>& g, vector<int>& ans ) {
  for ( auto t : g[x] ) {
    if ( ans[t] == -1 ) { ans[t] = ans[x]; dfs2(t, g, ans); }
  }
}


vector<int> SCC( const vector<vector<int>>& g ) {
  vector<pair<int,int>> ord( g.size(), make_pair(-1, -1));
  vector<int> ans(g.size(), -1);
  for ( int i = 0; i < g.size(); ++i ) ord[i].second = i;

  int no = 1;
  for ( int i = 0; i < ord.size(); ++i ) if ( ord[i].first == -1 ) no = dfs(i, no, g, ord);

  sort(ord.begin(), ord.end(), [](pair<int,int> p1, pair<int,int> p2 ) { return p1.first > p2.first; } );

  vector<vector<int>> rg( g.size() );
  for ( int i = 0; i < g.size(); ++i ) {
    for ( auto t : g[i] ) rg[t].push_back(i);
  }
  for ( int i = 0; i < ord.size(); ++i ) {
    int noden = ord[i].second;
    if ( ans[noden] == -1 ) {
      ans[noden] = noden;
      dfs2(noden, rg, ans);
    }
  }

  return ans;
}

int main()
{
  vector<vector<int>> g;
  vector<int> ans;
  int v,e;

  cin >> v >> e;
  g = vector<vector<int>>(v);
  for ( int i = 0; i < e; ++i ) {
    int s,t; cin >> s >> t;
    g[s].push_back(t);
  }

  ans = SCC(g);
  
  int q; cin >> q;
  while(q--) {
    int u,v; cin >> u >> v;
    if ( ans[u] == ans[v] ) cout << 1 << endl;
    else cout << 0 << endl;
  }
}
