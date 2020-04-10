#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ii = pair<int, int>;
using vi = vector<int>;

int n;
set<interval> st;

vector<interval> setRange(int L, int R, int x) { // set A[L...R] = x
  auto lit = --st.upper_bound({L,0,0}); // L \in *lit
  auto rit = st.upper_bound({R,0,0}); // R \in *prev(rit)

  int lb = lit -> l, rb = prev(rit) -> r;
  int lx = lit -> x, rx = prev(rit) -> x;

  vector<interval> ret;
  for(auto it = lit; it != rit; ++it) {
    ret.push_back({max(L, it -> l), min(R, it -> r), it -> x});
  }

  st.erase(lit, rit);

  if(lb < L) st.insert(rit, {lb, L-1, lx});
  st.insert(rit, {L, R, x});
  if(rb > R) st.insert(rit, {R+1, rb, rx});

  return ret;
}

int main(int argc, char const *argv[])
{
#ifdef LOCAL
  freopen("in", "r", stdin);
#endif
  for(int i = 1; i <= n; i++) {
    st.insert({i, i, i});
  }
}
