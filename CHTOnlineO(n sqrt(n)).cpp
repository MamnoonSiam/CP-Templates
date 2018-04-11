struct GodBlessCHT {
    typedef long long ll;
    typedef double ld;
    struct Line {
        ll m, c; Line() {}
        Line(ll _m, ll _c) :
            m(_m), c(_c) {}
        ld operator & (const Line &l) const {
            return ld(l.c-c)/ld(m-l.m); }
        ll evaluate(ll x) {
            return m * x + c; }
        bool operator < (const Line &l) {
            return m < l.m; }
    };
    int magic, whole;
    vector<Line> hull, sack, ram;
    vector<ld> stars;
    GodBlessCHT() {
        magic = 1000;
        whole = 1000000;
        hull.reserve(whole+10);
        sack.reserve(magic+10);
        stars.reserve(whole+10);
        ram.reserve(whole+10);
    }
    void addline(Line l) {
        hull.push_back(l);
        int s = hull.size();
        while(hull.size() > 2 and (hull[s-3] & hull[s-1]) < (hull[s-3] & hull[s-2]))
            hull.erase(hull.end()-2), stars.pop_back(), s--;
        if(hull.size() > 1 and hull[s-2].m == hull[s-1].m) {
            hull.pop_back(); return;
        }
        if(hull.size()) stars.push_back(hull[s-2] & hull[s-1]);
        else stars.push_back(-numeric_limits<ld>::infinity());
    }
    void refresh() {
        sort(all(sack)), reverse(all(sack));
        ram = hull;
        stars.clear(), hull.clear();
        int i = 0, j = 0;
        while(i < ram.size() or j < sack.size()) {
            if(i < ram.size() and j < sack.size()) {
                if(sack[j] < ram[i]) {
                    addline(ram[i]); i++;
                } else {
                    addline(sack[j]); j++;
                }
            } else if(i < ram.size()) {
                addline(ram[i]); i++;
            } else {
                addline(sack[j]); j++;
            }
        } sack.clear();
    }
    void insert(ll m, ll c) {
        Line l(m, c);
        sack.push_back(l);
        if(sack.size() == magic)
            refresh();
    }
    ll bruteforce(ll x) {
        ll ret = LLONG_MAX;
        for(int i=0; i<sack.size(); i++) {
            ret = min(ret, sack[i].evaluate(x));
        } return ret;
    }
    ll query(ll x) {
        int i = upper_bound(all(stars), ld(x))-stars.begin();
        return min(hull.size() ? hull[i-1].evaluate(x) : LLONG_MAX, bruteforce(x));
    }
};
