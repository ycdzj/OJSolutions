#include <cstdio>
const int MAXN = 1e6 + 5;
int n, p;
inline int addmod(int a, int b) { return (a + b) % p; }
inline int mulmod(long long a, int b) { return (a * b) % p; }
inline int powmod(int a, int x) {
	long long cur = a, res = 1;
	while(x) {
		if(x & 1) res = (res * cur) % p;
		cur = (cur * cur) % p;
		x >>= 1;
	}
	return res;
}
int fac[MAXN], inv_fac[MAXN];
int com(int n, int m) {
	return mulmod(fac[n], mulmod(inv_fac[n - m], inv_fac[m]));
}
int f[MAXN], sz[MAXN];
int main() {
	scanf("%d%d", &n, &p);
	fac[0] = 1;
	for(int i = 1; i <= n; i++) fac[i] = mulmod(fac[i - 1], i);
	inv_fac[n] = powmod(fac[n], p - 2);
	for(int i = n - 1; i >= 0; i--) inv_fac[i] = mulmod(inv_fac[i + 1], i + 1);

	for(int i = n; i >= 1; i--) {
		sz[i] = 1;
		int l = 0;
		if(i * 2 <= n) {
			sz[i] += sz[i * 2];
			l = sz[i * 2];
		}
		if(i * 2 + 1 <= n) sz[i] += sz[i * 2 + 1];
		f[i] = com(sz[i] - 1, l);
		if(i * 2 <= n) f[i] = mulmod(f[i], f[i * 2]);
		if(i * 2 + 1 <= n) f[i] = mulmod(f[i], f[i * 2 + 1]);
	}
	printf("%d\n", f[1]);
	return 0;
}
