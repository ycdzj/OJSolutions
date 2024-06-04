#include <cstdio>
const int MAXN = 1000 + 5;
const int MOD = 998244353;
inline int addmod(int a, int b) { return (a + b) % MOD; }
int f[MAXN][MAXN * 2][4];
int n, m;
int main() {
	scanf("%d%d", &n, &m);
	f[1][1][0] = f[1][1][3] = f[1][2][1] = f[1][2][2] = 1;
	for(int i = 2; i <= n; i++) for(int j = 1; j <= m; j++) for(int k = 0; k < 4; k++){
		for(int kk = 0; kk < 4; kk++) {
			int cnt0 = 4;
			if((k & 1) == (k >> 1 & 1)) cnt0--;
			if((kk & 1) == (kk >> 1 & 1)) cnt0--;
			if((k & 1) == (kk & 1)) cnt0--;
			if((kk >> 1 & 1) == (k >> 1 & 1)) cnt0--;
			if(cnt0 == 0) cnt0 = 1;
			int cnt1 = 2;
			if((kk & 1) == (kk >> 1 & 1)) cnt1--;
			int jj = j + cnt1 - cnt0;
			if(jj > 0) f[i][j][k] = addmod(f[i][j][k], f[i - 1][jj][kk]);
		}
	}
	int ans = 0;
	for(int k = 0; k < 4; k++) ans = addmod(ans, f[n][m][k]);
	printf("%d\n", ans);
	return 0;
}