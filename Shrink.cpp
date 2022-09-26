//座標圧縮

#include<vector>
#include<set>
#include<iostream>
#include<algorithm>

using namespace std;

using ll = long long;

class Shrink {
    vector<int> ord;

    public:
    Shrink( const vector<int>& v ) {
        set<int> s;

        for ( auto i : v ) s.insert(i);
        for ( auto i : s ) ord.push_back(i);
    }

    int get(int x ) {
        if ( x < ord[0] ) return -1;
        // if ( x > ord.back() ) return ord.size()+1;
        auto it = lower_bound(ord.begin(), ord.end(), x);
        return it-ord.begin();
    }

    vector<int> get_array(const vector<int>& v ) {
        vector<int> ans(v.size());
        for ( int i = 0; i < v.size(); ++i ) ans[i] = get(v[i]);
        return ans;
    }

};

int main()
{
    vector<int> v = {5, 10, 25, 7, 11, 100};

    Shrink sh(v);

    cout << sh.get(-1) << endl;
    cout << sh.get(7) << endl;
    cout << sh.get(200) << endl;
}
