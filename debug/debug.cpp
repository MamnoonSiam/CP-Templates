#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ii = pair<int, int>;
using vi = vector<int>;
#define all(v) begin(v), end(v)
#define sz(v) (int)(v).size()
#define fi first
#define se second
#ifdef LOCAL
#include "debug.h"
#else
#define debug(...)
#endif

int main(int argc, char const *argv[])
{
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);
#ifdef LOCAL
  freopen("in", "r", stdin);
#endif
  vector<char> v = {'a', 'b', 'c', 'd'};
  debug(v);
  vector<vector<char>> x = {v};
  debug(x);
  map<int, int> mp;
  mp[1] = 1;
  mp[2] = 2;
  debug(mp);
  set<int> st;
  st.insert(1);
  st.insert(2);
  debug(st);
  vector<bitset<3>> y = {bitset<3>(7)};
  debug(y);
  array<int, 10> ar;
  debug(ar);
  queue<int> Q;
  Q.push(10);
  debug(Q);
  priority_queue<int> pq;
  pq.push(1);
  pq.push(2);
  debug(pq);
  priority_queue<int, vector<int>, greater<int>> mpq;
  mpq.push(1);
  mpq.push(2);
  debug(mpq);
  deque<int> dq = {1, 2, 3, 4};
  debug(dq);
  multiset<int> ms;
  ms.insert(1);
  ms.insert(2);
  ms.insert(2);
  debug(ms);
  return 0;
}
/*
* use std::array instead of std::vector, if u can
* overflow?
* array bounds
*/