struct ConvexHullTrick {
	vector<ll> M, B;
	vector<double> left;
	ConvexHullTrick() {}
	bool bad(ll m1, ll b1, ll m2, ll b2, ll m3, ll b3) {
		// Careful, this may overflow
		return (b3-b1)*(m1-m2) < (b2-b1)*(m1-m3);
	}
	// Lines must be added in decreasing order of slope.
	void add(ll m, ll b) {
		while (M.size() >= 2 and bad(M[M.size()-2], B[B.size()-2], M.back(), B.back(), m, b))
			M.pop_back(), B.pop_back(), left.pop_back();
		if (M.size() && M.back() == m) {
			if (B.back() > b)
				M.pop_back(), B.pop_back(), left.pop_back();
			else return;
		}
		if (M.size() == 0)
			left.push_back(-numeric_limits<double>::infinity());
		else
			left.push_back((double)(b - B.back())/(M.back() - m));
		M.push_back(m);
		B.push_back(b);
	}
	// Get the minimum value of mx + b among all lines in the structure.
	// There must be at least one line.
	ll query(ll x) {
		int i = upper_bound(left.begin(), left.end(), x) - left.begin();
		return M[i-1]*x + B[i-1];
	}
}cht;
