#include  <bits/stdc++.h>
using namespace std;

#define debug(x) cout << #x << " = " << x << endl;

const int maxn = 1e5 + 5;
using ll = long long;
#define v second
#define w first
using ii = pair<ll, int>;

int n, m, k, q;
vector<ii> g[maxn];
ll e[maxn];
int dad[maxn];
bool done[maxn];
vector<vector<ll>> egs;
vector<vector<ll>> negs;
vector<vector<ll>> tegs;
int par[maxn];
vector<ii> tr[maxn];
int t[17][maxn];
ll mx[17][maxn];
int lvl[maxn];

int find(int u) {
	return par[u] == u ? u : par[u] = find(par[u]);
}
int unite(int u, int v) {
	u = find(u);
	v = find(v);
	if(u == v) return 0;
	par[u] = v;
	return 1;
}

int cnt = 0;
void dfs(int u) {
	cnt++;
	for(ii &x : tr[u]) {
		if(x.v != t[0][u]) {
			t[0][x.v] = u;
			mx[0][x.v] = x.w;
			lvl[x.v] = lvl[u] + 1;
			dfs(x.v);
		}
	}
}

ll query(int u, int v) {
	ll ret = 0;
	if(lvl[u] > lvl[v]) swap(u, v);
	int d = lvl[v] - lvl[u];
	for(int i = 16; i >= 0; i--) {
		if(d & (1 << i)) {
			ret = max(ret, mx[i][v]);
			v = t[i][v];
		}
	}
	if(u == v) return ret;
	for(int i = 16; i >= 0; i--) {
		if(t[i][u] != t[i][v]) {
			ret = max({ret, mx[i][u], mx[i][v]});
			u = t[i][u];
			v = t[i][v];
		}
	}
	return max({ret, mx[0][u], mx[v][0]});
}

int main(int argc, char const *argv[])
{
	// freopen("in", "r", stdin);
	scanf("%d %d %d %d", &n, &m, &k, &q);
	for(int i = 1; i <= m; i++) {
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);
		g[u].emplace_back(w, v);
		g[v].emplace_back(w, u);
		egs.push_back({u, v, w});
	}
	memset(e, (1 << 7) - 1, sizeof e);
	priority_queue<ii> Q;
	for(int i = 1; i <= k; i++) {
		e[i] = 0;
		dad[i] = i;
		Q.push({0, i});
	}
	while(Q.size()) {
		int u = Q.top().v;
		Q.pop();
		if(done[u]) continue;
		done[u] = 1;
		for(ii eg : g[u]) {
			if(e[eg.v] > e[u] + eg.w) {
				e[eg.v] = e[u] + eg.w;
				dad[eg.v] = dad[u];
				Q.push({-e[eg.v], eg.v});
			}
		}
	}
	for(auto &eg : egs) {
		int u = eg[0];
		int v = eg[1];
		ll w = eg[2];
		if(dad[u] != dad[v]) {
			ll nw = w + e[u] + e[v];
			int nu = dad[u];
			int nv = dad[v];
			negs.push_back({nw, nu, nv});
		}
	}
	iota(par, par + 1 + n, 0);
	sort(negs.begin(), negs.end());
	for(auto &eg : negs) {
		ll w = eg[0];
		ll u = eg[1];
		ll v = eg[2];
		if(unite(u, v)) {
			tegs.push_back({u, v, w});

			tr[u].emplace_back(w, v);
			tr[v].emplace_back(w, u);
		}
	}
	memset(t, -1, sizeof t);
	memset(mx, 0, sizeof mx);
	lvl[1] = 0;
	dfs(1);
	assert(cnt == k);
	for(int p = 1; p < 17; p++) {
		for(int i = 1; i <= k; i++) {
			int mid = t[p-1][i];
			if(mid != -1) {
				t[p][i] = t[p-1][mid];
				mx[p][i] = max(mx[p-1][i], mx[p-1][mid]);
			}
		}
	}
	while(q--) {
		int u, v;
		scanf("%d %d", &u, &v);
		ll ans = query(u, v);
		printf("%lld\n", ans);
	}
	return 0;
}
