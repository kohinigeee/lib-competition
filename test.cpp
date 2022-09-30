#include<iostream>
#include"PrefixSum.hpp"
#include"Mod.hpp"

using namespace std;

using ll = long long;

const static int p = 139;

Mod get( vector<Mod>& v, int l, int r ) {
  Mod ans = Mod(1);
  for ( int i = l; i <= r; ++i ) {
    ans = ans*v[i];
  }

  return ans;
}

int main()
{
  Mod::set(p);

  vector<Mod> v;
  int l = 0, r = 4;

  v.push_back(Mod(3));
  v.push_back(Mod(7));
  v.push_back(Mod(5));
  v.push_back(Mod(11));
  v.push_back(Mod(16));

  PrefixSum<Mod> ps( v, [](Mod& x, Mod& y) { return x*y; }, [](Mod& x, Mod& y){ return x/y; } );
  cout << get(v, l, r) << endl;
  cout << ps.get(l, r) << endl;

}