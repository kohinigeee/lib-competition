#include<iostream>
#include<utility>
#include<queue>
#include<algorithm>

using namespace std;

using prim_t = long long;

/*
Edge : pair<prim_t, prim_t>で表現(first:to, second:cost)
*/
class Prim {
    class Edge {
        public:
        prim_t s, t, c;
        Edge ( prim_t s, prim_t t, prim_t c ) : s(s), t(t), c(c) {}
    };

    static const prim_t s_no = 0;
    static const prim_t D_INF = (1LL<<60);
    vector<vector<pair<prim_t, prim_t>>> graph;
    vector<Edge> ans;
    prim_t minsum;

    void cal();

    public:
    Prim(vector<vector<pair<prim_t, prim_t>>>& graph) : graph(graph) {
        cal();
    }

    prim_t getSum() { return minsum; }

      void print() {
            for ( prim_t i = 0; i < ans.size(); ++i ) {
                Edge& e = ans[i];
                string s = "[" + to_string(i) + "]";
                s += " (" + to_string(e.s) + " - " + to_string(e.t) + ") cost:" + to_string(e.c);
                cout << s << endl;
            }
            cout << "total cost: " << minsum << endl;
        }
};

void Prim::cal() {
    vector<prim_t> d(graph.size());
    vector<Edge> edges(graph.size(), Edge(0, 0, 0));
    priority_queue<pair<prim_t, prim_t>, vector<pair<prim_t, prim_t>>, greater<pair<prim_t, prim_t>>> que;

    for ( auto& v : d ) v = D_INF;
    minsum = 0;
    d[s_no] = 0;
    que.push(make_pair(d[s_no], prim_t(s_no)));

    while(!que.empty()) {
        prim_t no_top = que.top().second;
        prim_t d_top = que.top().first;

        que.pop();

        if ( d[no_top] < d_top ) continue;
        minsum += d_top;
        if ( no_top != s_no ) ans.push_back(edges[no_top]);
        d[no_top] = -1;
        
        for ( auto e : graph[no_top] ) {
            prim_t no_to = e.first, c_to = e.second;
            if ( c_to < d[no_to] ) {
                d[no_to] = c_to;
                que.push(make_pair(d[no_to], no_to));
                edges[no_to] = Edge(min(no_top, no_to), max(no_top, no_to), c_to);
            }
        }
    }
}

int main()
{
    prim_t v, e;
    vector<vector<pair<prim_t, prim_t>>> graph;

    cin >> v >> e;
    graph = vector<vector<pair<prim_t, prim_t>>>(v);

    for ( int i = 0; i < e; ++i ) {
        prim_t s, t, w;
        cin >> s >> t >> w;
        graph[s].push_back(make_pair(t,w));
        graph[t].push_back(make_pair(s,w));
    }

    Prim prim(graph);
    cout << prim.getSum() << endl;
}