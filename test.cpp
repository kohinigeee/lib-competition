#ifndef INCLUDE_PREFIXSUM_HPP
#define INCLUDE_PREFIXSUM_HPP

#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

template<typename T>
class PrefixSum {
    vector<T> pres;
    T (*ope)(T&, T&);
    T (*rev)(T&, T&);

    public:

    PrefixSum( const vector<T>& values, T (*ope)(T&, T&), T (*rev) (T&, T&) ): ope(ope), rev(rev) {
        pres.push_back(values[0]);
        for ( int i = 1; i < values.size(); ++i ) {
            T tmp = values[i];
            (*ope)(pres[i-1], tmp);
            pres.push_back((*ope)(pres[i-1], tmp));
        }
    }


    T get(int l, int r ) { //閉区間 [l~r]の和を返す
        T ans = pres[r];
        if ( l > 0 ) {
            ans = (*rev)(ans, pres[l-1]);
        }
        return ans;
    }
};

template<>
class PrefixSum<long long> {
    vector<long long> pres;
    long long (*ope)(const long long, const long long);
    long long (*rev) (const long long, const long long);

    public:

    PrefixSum( const vector<long long>& values, long long (*ope)(const long long, const long long), long long (*rev) (const long long, const long long) ): ope(ope), rev(rev) {
        this->pres.push_back(values[0]);
        for ( int i = 1; i < values.size(); ++i ) {
            long long added = (*ope)(pres[i-1], values[i]);
            this->pres.push_back(added);
        }
    }


    PrefixSum( const vector<long long>& values ) : PrefixSum(values, [](const long long a, const long long b) {return a+b; }, [](const long long a, const long long b) {return a-b; } ) {}


    long long get(const int l, const int r ) const { //閉区間 [l~r]の和を返す
        if ( l < 0 || r >= pres.size() ) throw new exception();
        long long ans = pres[r];
        if ( l > 0 ) {
            ans =(*rev)(ans, pres[l-1]);
        }
        return ans;
    }
};

int main()
{
  vector<long long> a;
  int n, k;

  cin >> n >> k;
  for ( int i = 0; i < n; ++i ) {
    long long tmp;
    cin >> tmp;
    a.push_back(tmp);
  }

  PrefixSum<long long> ps(a);
  long long sum = 0;

  for ( int i = 0; i+k-1 < n; ++i ) {
    sum += ps.get(i, i+k-1);
  }
  cout << sum << endl;
}
#endif