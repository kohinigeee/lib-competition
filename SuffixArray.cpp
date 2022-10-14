#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<utility>

using namespace std;

vector<int> suffixArray(string t) {
    vector<int> ord(t.size(), -1);
    vector<int> v(t.size(), -1);
    int n = t.size();

    for ( int i = 0; i < v.size(); ++i ) { 
        v[i] = t[i];
        ord[i] = i;
    }

    sort(ord.begin(), ord.end(), [&v]( int x, int y) { return v[x] < v[y]; } );
    {
        int cnt = 0;
        vector<int> tmpv(n, -1);
        tmpv[ord[0]] = cnt;
        for ( int i = 1; i < n; ++i ) {
            if ( v[ord[i]] != v[ord[i-1]] ) ++cnt;
            tmpv[ord[i]] = cnt;
        }
        v = tmpv;
    }
    
    cout << "v : "; 
    for ( auto i : v ) cout << i << " "; cout << endl;

    for ( int i = 0; i < ord.size(); ++i ) v[ord[i]] = i;

    for ( auto v : ord ) cout << v << " "; cout << endl;

    int maxk = 1;
    while( maxk < t.size() ) maxk *= 2;

    for ( int k = 2; k <= maxk; k *= 2 ) {
        sort(ord.begin(), ord.end(), [n,k,&v]( int x, int y ) {
            if ( v[x] == v[y] ) {
                int j = k/2;
                int vx = ( x+j < n) ? v[x+j] : -1;
                int vy = ( y+j < n) ? v[y+j] : -1; 
                return vx < vy;
            }
            return v[x] < v[y];
        }); 

        int cnt = 0;
        int j = k/2;
        vector<int> tmpv(n, -1);
        tmpv[ord[0]] = cnt;

        for ( int i = 1; i < n; ++i ) {
            int v1 = v[ord[i-1]], v2 = v[ord[i]];
            int p1 = ( ord[i-1]+ j < n ) ? v[ord[i-1]+j] : -1 ; 
            int p2 = ( ord[i]+j < n ) ? v[ord[i]+j] : -1 ;

            if ( !(v1 == v2 && p1 == p2 ) ) ++cnt;
            tmpv[ord[i]] = cnt; 
        };
        v = tmpv;

        cout << "v: "; for ( auto i : v ) cout << i << " "; cout << endl;
       
    }

    return ord;
}

int main()
{
    string t;
    cin >> t;

    vector<int> ord = suffixArray(t);

    for ( auto v : ord ) cout << v << " "; cout << endl;
}