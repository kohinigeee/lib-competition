#include<iostream>
#include<vector>

#define INF (1LL<<60)

using namespace std;

using ll = long long;

class Edge {
    public:

    int to;
    ll cap; 

    Edge( int to, ll cap ): to(to), cap(cap) {} 
};

ll dfs(const vector<vector<Edge>>& g, vector<int>& visited, vector<int>& ord, int t, int x, ll mincost = INF ) {
    visited[x] = 1;
    ord.push_back(x);

    if ( x == t ) return mincost;

    for ( auto e : g[x] ) {
        if ( visited[e.to] ) continue;
        ll value = dfs( g, visited, ord, t, e.to, min(mincost, e.cap));
        if ( value != INF ) return value; 
    }
    ord.pop_back();
    return INF;
}

ll fordFulkerson( const vector<vector<Edge>>& g, vector<vector<ll>>& flow, int s, int t ) {
    flow = vector<vector<ll>>( g.size(), vector<ll>(g.size(), 0));
    vector<vector<ll>> caps( g.size(), vector<ll>(g.size(), 0));

    for ( int i = 0; i < g.size(); ++i ) for ( auto e : g[i] ) caps[i][e.to] = e.cap;

    ll maxflow = 0;

    while(1) {
        vector<vector<Edge>> tmpg(g.size());
        vector<int> ord;
        vector<int> visited(g.size(), 0);

        for ( int i = 0; i < g.size(); ++i ) {
            for ( int j = 0; j < g.size(); ++j ) {
                ll f = caps[i][j]-flow[i][j]+flow[j][i];
                if ( f > 0 ) tmpg[i].push_back(Edge(j, f));
            } 
        }
        ll mincost = dfs(tmpg, visited, ord, t, s);
        if ( mincost == INF ) break;
        maxflow += mincost;
        for ( int i = 0; i < ord.size()-1; ++i ) {
            int from = ord[i], to = ord[i+1];
            ll res = caps[from][to]-flow[from][to];
            flow[from][to] = min(flow[from][to]+mincost, caps[from][to]);
            ll tmpmin = max(mincost-res, 0LL);
            flow[to][from] -= tmpmin;
            
        } 
    }
    return maxflow;
}

int main()
{
    int v, e;
    vector<vector<Edge>> g;

    cin >> v >> e;
    g = vector<vector<Edge>>(v);
    while(e--) {
        int u, v;
        ll c;

        cin >> u >> v >> c;
        g[u].push_back(Edge(v,c));
    }

    vector<vector<ll>> flow;
    cout << fordFulkerson(g, flow, 0, v-1) << endl;
}