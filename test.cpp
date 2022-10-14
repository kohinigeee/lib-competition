#include<iostream>
#include<vector>
#include<string>
#include<algorithm>

using namespace std;

int main()
{
    string t;
    vector<string> subs;

    cin >> t;

    for ( int i = 0; i < t.size(); ++i ) {
        subs.push_back(t.substr(i, t.size()-i));
    }

    sort(subs.begin(), subs.end());

    for ( auto s : subs ) {
        cout << t.size()-s.size() << " ";
    }
    cout << endl;

}