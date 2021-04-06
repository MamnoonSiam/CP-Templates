#define m first
#define b second
using line = pair<ll, ll>;
using vline = vector<line>;

ll eval(const line& l, ll x) {
  return l.m * x + l.b;
}
line operator + (const line& l1, const line& l2) {
  return {l1.m + l2.m, l1.b + l2.b};
}
line operator - (const line& l1, const line& l2) {
  return {l1.m - l2.m, l1.b - l2.b};
}

// x(l1 & l2) <= x(l3 & l4)
bool cmp(line l1, line l2, line l3, line l4) {
  if(l1.m < l2.m) swap(l1, l2);
  if(l3.m < l4.m) swap(l3, l4);
  return (__int128)(l2.b-l1.b)*(l3.m-l4.m) <= (__int128)(l4.b-l3.b)*(l1.m-l2.m);
}

void add_line(vline &v, line l) {
  int s = sz(v);
  while(s >= 2 and cmp(v[s-2], l, v[s-2], v[s-1]))
    v.pop_back(), s--;
  if(s and v[s-1].m == l.m)
    v[s-1].b = max(v[s-1].b, l.b);
  else v.push_back(l);
}

// h(x) = f(x) + g(x)
vline add_hull(vline f, vline g) {
  if(f.empty() or g.empty()) return f.empty() ? g : f;
  vline h, v;
  add_line(h, f[0] + g[0]);
  int i = 1, j = 1;
  while(i < sz(f) or j < sz(g)) {
    if(i == sz(f)) {
      add_line(h, f[i-1] + g[j++]);
    } else if(j == sz(g)) {
      add_line(h, f[i++] + g[j-1]);
    } else {
      if(cmp(f[i-1], f[i], g[j-1], g[j])) {
        add_line(h, f[i++] + g[j-1]);
      } else {
        add_line(h, f[i-1] + g[j++]);
      }
    }
  }
  return h;
}

// h(x) = max(f(x), g(x))
vline max_hull(vline f, vline g) {
  int i = 0, j = 0;
  vline h;
  while(i < sz(f) and j < sz(g)) {
    if(f[i].m < g[j].m) add_line(h, f[i++]);
    else add_line(h, g[j++]);
  }
  while(i < sz(f)) add_line(h, f[i++]);
  while(j < sz(g)) add_line(h, g[j++]);
  return h;
}
