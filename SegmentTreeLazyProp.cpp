// A Lazy Propagation Sample
// Solution to a problem from SPOJ - LITE

#include <bits/stdc++.h>
using namespace std;

#define lc (node<<1)
#define rc (lc | 1)
#define mid (b + e >> 1)

const int maxn = 100010;

int cnt[maxn*4];
int lazy[maxn*4];

int n, m;

void apply(int node, int b, int e) {
	cnt[node] = (e-b+1)-cnt[node];
	if(b != e) {
		lazy[lc] ^= 1;
		lazy[rc] ^= 1;
	}
	lazy[node] = 0;
}

void update(int node, int b, int e, int i, int j) {
	if(lazy[node]) apply(node, b, e);
	if(b > j or e < i) return ;
	if(i <= b and e <= j) {
		lazy[node] ^= 1;
		if(lazy[node])
			apply(node, b, e);
		return ;
	}
	update(lc, b, mid, i, j);
	update(rc, mid+1, e, i, j);
	cnt[node] = cnt[lc] + cnt[rc];
}

int query(int node, int b, int e, int i, int j) {
	if(lazy[node]) apply(node, b, e);
	if(b > j or e < i) return 0;
	if(i <= b and e <= j) return cnt[node];
	return query(lc, b, mid, i, j) +
			query(rc, mid+1, e, i, j);
}

int32_t main () {
	cin>>n>>m;
	for(int i=1; i<=m; i++) {
		int op, l, r; cin>>op>>l>>r;
		if(!op) update(1, 1, n, l, r);
		else cout<<query(1, 1, n, l, r)<<endl;
	}
	return 0;
}
