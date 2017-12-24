typedef pair<int, int> ii;
typedef pair<ii, int> ppi;

const int maxn = 100010; // edit here
const int maxlg = 18; // edit here

int sp[maxlg][maxn];
string s;

void BuildTable() {
	MEMSET(sp, -1);
	vector<ppi> temp;
	for(int i=0; i<s.size(); i++) sp[0][i] = s[i] - 'a'; // edit here
	for(int p = 1; (1 << p) <= s.size(); p++) {
		temp.clear();
		for(int i = 0; i + (1 << p) - 1 < s.size(); i++) {
			temp.push_back(ppi(ii( sp[p-1][i], sp[p-1][i + (1 << (p-1))] ), i));
		}
		sort(all(temp));
		int c = 0; sp[p][temp[0].second] = c;
		for(int i = 1; i<temp.size(); i++) {
			if(temp[i].first != temp[i-1].first) c++;
			sp[p][temp[i].second] = c;
		}
	}
}

int LongestCommonPrefix(int i, int j) {
	int len = 0;
	for(int p = 17; p >= 0 and i < s.size() and j < s.size(); p--) {
		if(j + (1<<p) - 1 > s.size() - 1) continue;
		if(sp[p][i] == sp[p][j]) {
			i += (1 << p);
			j += (1 << p);
			len += (1 << p);
		}
	}
	return len;
}

int LongestCommonPrefix(ii x, ii y) {
	int i = x.first, j = x.second;
	int l = y.first, r = y.second;
	int lcp = LongestCommonPrefix(i, l);
	j = min(j, i + lcp - 1);
	r = min(r, l + lcp - 1);
	return min(j-i, r-l) + 1;
}

bool LessOperator(ii x, ii y) {
	int i = x.first, j = x.second;
	int l = y.first, r = y.second;
	int lcp = LongestCommonPrefix(i, l);
	if(i + lcp - 1 >= j or l + lcp - 1 >= r) return j-i < r-l;
	return s[i + lcp] < s[l + lcp];
}
