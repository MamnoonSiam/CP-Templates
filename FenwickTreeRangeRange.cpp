template<typename T>
struct fenwick_tree {
  // 1-indexed, ranges are inclusive
  T *B1, *B2;
  int N;
  fenwick_tree(int _N) : N(_N) {
    B1 = new T[N+1], B2 = new T[N+1];
    #define clr(v) fill(v, v+(N+1), 0)
    clr(B1), clr(B2);
    #undef clr
  }
  ~fenwick_tree() { delete [] B1, delete [] B2; }
  void add(T* B, int idx, T value) {
    for(; idx <= N; idx += idx & -idx) B[idx] += value;
  }
  void range_add(int l, int r, T value) {
    add(B1, l, value);
    add(B1, r+1, -value);
    add(B2, l, value * (l-1));
    add(B2, r+1, -value * r);
  }
  T sum(T* B, int idx, T ret = 0) {
    for(; idx > 0; idx -= idx & -idx) {
      ret += B[idx];
    } return ret;
  }
  T prefix_sum(int idx) {
    return sum(B1, idx) * idx - sum(B2, idx);
  }
  T range_sum(int l, int r) {
    return prefix_sum(r) - prefix_sum(l-1);
  }
};
