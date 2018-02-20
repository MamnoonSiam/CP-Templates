struct ConvexHullTrick {
    // keeps upper-hull for minimums
    // slopes are decreasing, queries are increasing
    typedef long long ll;
    struct Line {
        ll m, c; Line(){}
        Line(ll _m, ll _c) { m = _m, c = _c; }
        // for getting x-axis of intersections
        double operator & (const Line &l) const {
            return double(l.c-c)/double(m-l.m); }
        ll evaluate(ll x) { return m*x + c; }
    };
    vector<Line> hull; // lines
    vector<double> stars; // x-axes of intersections
    int ptr = -1;
    void addline(ll m, ll c) {
        Line l = Line(m, c);
        while(hull.size() >= 2 and (hull[hull.size()-2] & l) < stars.back())
            hull.pop_back(), stars.pop_back();
        // handles parallel lines
        if(hull.size() and hull.back().m == l.m) {
            if(hull.back().c > l.c)
                hull.pop_back(), stars.pop_back();
            else return;
        }
        if(hull.size()) stars.push_back(hull.back() & l);
        else stars.push_back(-numeric_limits<double>::infinity());
        hull.push_back(l);
    }
    ll query(ll x) {
        ptr = min(ptr, (int)stars.size()-1); // in case, some lines were removed
        while(ptr+1 < (int)stars.size() and stars[ptr+1] <= double(x)) ptr++;
        return hull[ptr].evaluate(x); // prt+1 is the number of stars[i] <= x
        // as we are dealing with 0-indexing, we start from -1 and update it also with sz-1
    }
    ll query(ll x) {
        int i = upper_bound(all(stars), double(x))-stars.begin();
        return hull[i-1].evaluate(x);
    }
};
