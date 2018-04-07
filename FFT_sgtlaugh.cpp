#include <stdio.h>
#include <bits/stdtr1c++.h>

#define MAX 1048576
#define MOD 998244353
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)
#define dbg(x) cout << #x << " = " << x << endl
#define ran(a, b) ((((rand() << 15) ^ rand()) % ((b) - (a) + 1)) + (a))

#pragma GCC optimize("Ofast,no-stack-protector")
#pragma GCC optimize("unroll-loops")

using namespace std;

long long inv[MAX], fact[MAX], P[MAX], Q[MAX];

namespace fft{
    long long C[MAX], D[MAX];
    int len, last = -1, step = 0, rev[MAX];

	struct complx{
        long double real, img;

        inline complx(){
            real = img = 0.0;
        }

        inline complx conjugate(){
            return complx(real, -img);
        }

        inline complx(long double x){
            real = x, img = 0.0;
        }

        inline complx(long double x, long double y){
            real = x, img = y;
        }

        inline complx operator + (complx other){
            return complx(real + other.real, img + other.img);
        }

        inline complx operator - (complx other){
            return complx(real - other.real, img - other.img);
        }

        inline complx operator * (complx other){
            return complx((real * other.real) - (img * other.img), (real * other.img) + (img * other.real));
        }
    } u[MAX], v[MAX], f[MAX], g[MAX], dp[MAX], inv[MAX];

    inline long long round_half_even(long double x){
        long long res = abs(x) + 0.5;
        if (x < 0) res = -res;
        return res;
    }

    void build(int& a, long long* A, int& b, long long* B){
        while (a > 1 && A[a - 1] == 0) a--;
        while (b > 1 && B[b - 1] == 0) b--;

	    len = 1 << (32 - __builtin_clz(a + b) - (__builtin_popcount(a + b) == 1));
        for (int i = a; i < len; i++) A[i] = 0;
        for (int i = b; i < len; i++) B[i] = 0;

		if (!step++){
            dp[1] = inv[1] = complx(1);
            for (int i = 1; (1 << i) < MAX; i++){
                double theta = (2.0 * acos(0.0)) / (1 << i);
                complx mul = complx(cos(theta), sin(theta));
                complx inv_mul = complx(cos(-theta), sin(-theta));

                int lim = 1 << i;
                for (int j = lim >> 1; j < lim; j++){
                    dp[2 * j] = dp[j], inv[2 * j] = inv[j];
                    inv[2 * j + 1] = inv[j] * inv_mul;
                    dp[2 * j + 1] = dp[j] * mul;
                }
            }
        }

        if (last != len){
            last = len;
            int bit = (32 - __builtin_clz(len) - (__builtin_popcount(len) == 1));
            for (int i = 0; i < len; i++) rev[i] = (rev[i >> 1] >> 1) + ((i & 1) << (bit - 1));
        }
	}

	void transform(complx *in, complx *out, complx* ar){
	    for (int i = 0; i < len; i++) out[i] = in[rev[i]];
	    for (int k = 1; k < len; k <<= 1){
            for (int i = 0; i < len; i += (k << 1)){
                complx z, *a = out + i, *b = out + i + k, *c = ar + k;
                if (k == 1){
                    z = (*b) * (*c);
                    *b = *a - z, *a = *a + z;
                }

                for (int j = 0; j < k && k > 1; j += 2, a++, b++, c++){
                    z = (*b) * (*c);
                    *b = *a - z, *a = *a + z;
                    a++, b++, c++;
                    z = (*b) * (*c);
                    *b = *a - z, *a = *a + z;
                }
            }
	    }
	}

	bool equals(int a, long long* A, int b, long long* B){
        if (a != b) return false;
        for (a = 0; a < b && A[a] == B[a]; a++){}
        return (a == b);
	}

	int square(int a, long long* A){
	    int p_len = a + a - 1;

        build(a, A, a, A);
        for (int i = 0; i < len; i++) u[i] = complx(A[i], 0);
        transform(u, f, dp);
        for (int i = 0; i < len; i++) u[i] = f[i] * f[i];
        transform(u, f, inv);

        for (int i = 0; i < len; i++) A[i] = round_half_even(f[i].real / (long double)len);
        for (int i = len; i < p_len; i++) A[i] = 0;
        return p_len;
	}

	int mod_multiply(int a, long long* A, int b, long long* B, int mod){
	    int p_len = a + b - 1;

	    build(a, A, b, B);
	    int flag = equals(a, A, b, B);
	    for (int i = 0; i < len; i++) A[i] %= mod, B[i] %= mod;
	    for (int i = 0; i < len; i++) u[i] = complx(A[i] & 32767, A[i] >> 15);
	    for (int i = 0; i < len; i++) v[i] = complx(B[i] & 32767, B[i] >> 15);

		transform(u, f, dp);
		for (int i = 0; i < len; i++) g[i] = f[i];
		if (!flag) transform(v, g, dp);

		for (int i = 0; i < len; i++){
            int j = (len - 1) & (len - i);
            complx c1 = f[j].conjugate(), c2 = g[j].conjugate();

            complx a1 = (f[i] + c1) * complx(0.5, 0);
			complx a2 = (f[i] - c1) * complx(0, -0.5);
			complx b1 = (g[i] + c2) * complx(0.5 / len, 0);
			complx b2 = (g[i] - c2) * complx(0, -0.5 / len);
			v[j] = a1 * b2 + a2 * b1;
			u[j] = a1 * b1 + a2 * b2 * complx(0, 1);
		}
		transform(u, f, dp);
		transform(v, g, dp);

        long long x, y, z;
		for (int i = 0; i < len; i++){
            x = f[i].real + 0.5, y = g[i].real + 0.5, z = f[i].img + 0.5;
            A[i] = (x + ((y % mod) << 15) + ((z % mod) << 30)) % mod;
		}
		for (int i = len; i < p_len; i++) A[i] = 0;
		return p_len;
	}
}

vector <int> mod_multiply(vector <int>& A, vector <int>& B, int mod){
    int i, n = A.size(), m = B.size();
    for (i = 0; i < n; i++) P[i] = A[i];
    for (i = 0; i < m; i++) Q[i] = B[i];

    vector <int> C;
    int len = fft::mod_multiply(n, P, m, Q, mod);
    for (i = 0; i < len; i++) C.push_back(P[i]);
    return C;
}

vector <int> stirling1(int l, int r, int mod){
    if ((r - l) == 1) return {l % mod, 1 % mod};

    int m = (l + r) >> 1;
    vector <int> A = stirling1(l, m, mod);
    vector <int> B = stirling1(m, r, mod);
    return mod_multiply(A, B, mod);
}
