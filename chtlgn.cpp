struct ExpandableHull {
    typedef long long ll;
    typedef pair<ll, ll> pll;

    struct ConvexHullTrix {
        vector<ll> m, b;
        ConvexHullTrix() {}
        ConvexHullTrix(vector<pll> &lines) {
            for(pll &x : lines) add(x.first, x.second);
        }
        void init (vector<pll> &lines) {
            clear();
            for(pll &x : lines) add(x.first, x.second);
        }
        inline ll f(int idx, ll x) { return m[idx] * x + b[idx]; }
        bool bad(int l1, int l2, int l3) {
            return 1.0 * (b[l2] - b[l1]) * (m[l1] - m[l3]) >= 1.0 * (b[l3] - b[l1]) * (m[l1] - m[l2]);
        }
        void add(ll _m, ll _b) {
            m.emplace_back(_m), b.emplace_back(_b);
            int sz = m.size();
            while(sz >= 3 and bad(sz - 3, sz - 2, sz - 1)) {
                m.erase(m.end() - 2);
                b.erase(b.end() - 2);
                sz--;
            }
        }
        ll query(ll x) {
            int lo = 1, hi = m.size() - 1, mid, ret = 0;
            while(lo <= hi) {
                mid = lo + hi >> 1;
                if(f(mid, x) > f(mid - 1, x)) hi = mid - 1;
                else ret = mid, lo = mid + 1;
            } return f(ret, x);
        }
        void clear() {
            m.clear(), b.clear();
        }
    };

    vector<pll> bit[21];
    ConvexHullTrix cht[21];
    
    ExpandableHull() {}
    void add(ll _m, ll _b) {
        // _m = -_m, _b = -_b; // for maximum
        vector<pll> tmp(1, pll(_m, _b)), mrg(1, pll(_m, _b));
        int z = 0;
        for(int i = 0; i < 20; i++) {
            if(bit[i].size() == 0) { z = i; break; }
            mrg.clear();
            merge(all(bit[i]), all(tmp), back_inserter(mrg), [](pll &x, pll &y){return x > y;});
            tmp = mrg, bit[i].clear(), cht[i].clear();
        }
        bit[z] = mrg;
        cht[z].init(bit[z]);
    }
    ll query(ll x) {
        ll ret = 1e18;
        for(int i = 0; i < 20; i++) if(bit[i].size()) {
            ret = min(ret, cht[i].query(x));
        } return ret; // edit here for maximum
    }
};
