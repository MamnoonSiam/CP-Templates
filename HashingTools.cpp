#define int long long

const int maxn = 1000010;

int bigmod(int b, int p, int m, int ret = 1) {
	while(p) {
		if(p & 1) ret = (ret * b) % m;
		p >>= 1, b *= b, b %= m;
	} return ret;
}

int base[] = {401, 541, 691};
int mod[] = {999990011, 999994603, 999999937};
int inv[3][maxn], po[3][maxn];

struct hashval {
	int val[3];
	hashval() { memset(val, 0, sizeof val); }
	hashval(int _x, int _y, int _z) {
		val[0] = _x; val[1] = _y; val[2] = _z;
	}
	bool operator < (const hashval &temp) const {
		for(int i=0; i<3; i++) {
			if(val[i] != temp.val[i]) return val[i] < temp.val[i];
		} return false;
	}
	bool operator == (const hashval &temp) const {
		for(int i=0; i<3; i++) if(val[i] != temp.val[i]) return false; return true;
	}
	bool operator != (const hashval &temp) const {
		return !(*this == temp);
	}
};

struct FullHash {
	vector<int> h[3];
	FullHash() {}
	FullHash(char *str, int N) {
		for(int i=0; i<3; i++) {
			h[i].reserve(N+10);
			h[i].assign(N+10, 0);
		}
		for(int i=0; i<3; i++) {
			for(int j=1; j<=N; j++) {
				h[i][j] = (h[i][j-1] + po[i][j]*str[j]) % mod[i];
			}
		}
	}
	hashval SubStringHash(int i, int j) {
		int p = (((h[0][j] - h[0][i-1] + mod[0]) % mod[0]) * inv[0][i-1]) % mod[0];
		int q = (((h[1][j] - h[1][i-1] + mod[1]) % mod[1]) * inv[1][i-1]) % mod[1];
		int r = (((h[2][j] - h[2][i-1] + mod[2]) % mod[2]) * inv[2][i-1]) % mod[2];
		return hashval(p,q,r);
	}
};

void PrepareForHash() {
	for(int i=0; i<3; i++) {
		po[i][0] = 1;
		for(int j=1; j<=1000000; j++) {
			po[i][j] = (po[i][j-1] * base[i]) % mod[i];
		}
		inv[i][0] = 1; inv[i][1] = bigmod(po[i][1], mod[i]-2, mod[i]);
		for(int j=1; j<=1000000; j++) {
			inv[i][j] = (inv[i][j-1] * inv[i][1]) % mod[i];
		}
	}
}
