#include <cstdio>
const int MAXN = 1e5 + 5;
const int MOD = 20130427;
inline int addmod(int a, int b) { return (a + b) % MOD; }
inline int mulmod(long long a, int b) { return (a * b) % MOD; }
int b;
int powb[MAXN], g[MAXN], h[MAXN], f[MAXN], a[MAXN], sum[MAXN];
int solve(int *num, int len) {
	int p = 0;
	while(p < len && num[p] == 0) p++;
	int pre_ans = 0, res = 0;
	for(int i = p; i < len; i++) {
		int cur = num[i];
		if(i == p) cur--;
		int t1 = mulmod(powb[len - i - 1], pre_ans);
		int t2 = mulmod(i - p + 1, a[len - i - 1]);
		int t = addmod(t1, addmod(t2, f[len - i - 1]));
		int q = mulmod(mulmod(sum[num[i]], i - p + 1), mulmod(powb[len - i - 1], h[len - i - 1]));
		res = addmod(res, addmod(mulmod(t, cur), q));
		pre_ans = addmod(pre_ans, mulmod(mulmod(num[i], h[len - i - 1]), i - p + 1));
	}
	for(int i = p + 1; i < len; i++) {
		int t1 = mulmod(sum[b], mulmod(h[len - i - 1], powb[len - i - 1]));
		int t2 = addmod(f[len - i - 1], a[len - i - 1]);
		res = addmod(res, addmod(t1, mulmod(b - 1, t2)));
	}
	return res;
}
int n, m, l[MAXN], r[MAXN];
int main() {
	scanf("%d", &b);
	scanf("%d", &n);
	for(int i = 0; i < n; i++) scanf("%d", &l[i]);
	scanf("%d", &m);
	for(int i = 1; i <= m; i++) scanf("%d", &r[i]);
	r[m]++;
	for(int i = m; r[i] >= b; i--) {
		r[i] -= b;
		r[i - 1]++;
	}

	powb[0] = 1;
	h[0] = 1;
	g[0] = 1;
	a[0] = 0;
	sum[1] = 0;
	for(int i = 2; i < MAXN; i++) sum[i] = addmod(sum[i - 1], i - 1);
	for(int i = 1; i < MAXN; i++) {
		powb[i] = mulmod(powb[i - 1], b);
		h[i] = addmod(h[i - 1], powb[i]);
		g[i] = addmod(g[i - 1], h[i]);
		a[i] = addmod(mulmod(powb[i - 1], mulmod(sum[b], h[i - 1])), mulmod(b, a[i - 1]));
	}

	f[0] = 0;
	for(int i = 1; i < MAXN; i++) {
		int t = h[i - 1];
		if(i - 2 >= 0) t += g[i - 2];
		int p = mulmod(sum[b], powb[i - 1]);
		f[i] = addmod(mulmod(p, t), mulmod(b, f[i - 1]));
	}

	int ans_l = solve(l, n), ans_r = solve(r, m + 1);
	printf("%d\n", addmod(ans_r, MOD - ans_l));
	return 0;
}
