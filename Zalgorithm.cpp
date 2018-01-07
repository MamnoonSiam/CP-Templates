vector<int> zalgo(string s) {
	int n = s.size(), x = 0, y = 0;
	vector<int> z(n);
	for (int i = 1; i < n; i++) {
		z[i] = max(0,min(z[i-x],y-i+1));
		while (i+z[i] < n && s[z[i]] == s[i+z[i]]) {
			x = i; y = i+z[i]; z[i]++;
		}
	}
	return z;
}
