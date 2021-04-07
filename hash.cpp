const ll m1 = 916969619;
const ll m2 = 998244353;
const ll b1 = 101;
const ll b2 = 103;

struct hs {
  ll x = 0, y = 0;
  hs () {}
  hs(ll _x, ll _y) : x(_x), y(_y) {
    assert(0 <= x and x < m1);
    assert(0 <= y and y < m2);
  }
  bool operator == (const hs& o) const {
    return x == o.x and y == o.y;
  }
  bool operator != (const hs& o) const {
    return x != o.x or y != o.y;
  }
  hs operator + (const hs& o) const {
    hs r = o;
    if((r.x += x) >= m1) r.x -= m1;
    if((r.y += y) >= m2) r.y -= m2;
    return r;
  }
  hs& operator += (const hs& o) {
    return *this = *this + o;
  }
  hs operator * (const hs& o) const {
    hs r = o;
    if((r.x *= x) >= m1) r.x %= m1;
    if((r.y *= y) >= m2) r.y %= m2;
    return r;
  }
  hs& operator *= (const hs& o) {
    return *this = *this * o;
  }
  hs operator - (const hs& o) const {
    hs r(x, y);
    if((r.x -= o.x) < 0) r.x += m1;
    if((r.y -= o.y) < 0) r.y += m2;
    return r;
  }
  hs& operator -= (const hs& o) {
    return *this = *this - o;
  }
};
ostream& operator << (ostream& os, const hs& h) {
  os << "(" << h.x << "," << h.y << ")";
  return os;
}
hs base(b1, b2), base_inv(qpow(b1, m1-2, m1), qpow(b2, m2-2, m2));

pw[0] = inv[0] = hs(1, 1);
for(int i = 1; i < N; ++i) {
  pw[i] = pw[i-1] * base;
  inv[i] = inv[i-1] * base_inv;
}
