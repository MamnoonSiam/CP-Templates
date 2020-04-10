template<typename T>
struct fenwick_tree {
  // 1-indexed, ranges are inclusive
  vector<T> B1, B2;
  int N;
  fenwick_tree() { N = 0; }
  fenwick_tree(int _N) : N(_N) {
    B1.assign(N+1, 0), B2.assign(N+1, 0);
  }
  void add(vector<T>& B, int p, T x) {
    for(; p <= N; p += p & -p) B[p] += x;
  }
  void range_add(int l, int r, T x) {
    add(B1, l, x);
    add(B1, r+1, -x);
    add(B2, l, x*(l-1));
    add(B2, r+1, -x*r);
  }
  T sum(vector<T>& B, int p, T ret = 0) {
    for(; p > 0; p -= p & -p) {
      ret += B[p];
    } return ret;
  }
  T prefix_sum(int p) {
    return sum(B1, p) * p - sum(B2, p);
  }
  T range_sum(int l, int r) {
    return prefix_sum(r) - prefix_sum(l-1);
  }
};
