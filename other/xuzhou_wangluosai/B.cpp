#include <cstdio>
#include <cstring>

const int MAXN = 64;
void mat_mul(int res[][MAXN], int a[][MAXN], int b[][MAXN], int n, int m, int k) {
	static int buf[MAXN][MAXN];
	for(int i = 0; i < n; i++) for(int j = 0; j < k; j++) {
		buf[i][j] = 0;
		for(int x = 0; x < m; x++) buf[i][j] ^= (a[i][x] & b[x][j]);
	}
	for(int i = 0; i < n; i++) for(int j = 0; j < k; j++) res[i][j] = buf[i][j];
}
void mat_pow(int res[][MAXN], int a[][MAXN], int x, int n) {
	static int bufa[MAXN][MAXN];
	for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) {
		bufa[i][j] = a[i][j];
		res[i][j] = (i == j) ? 1 : 0;
	}
	while(x) {
		if(x & 1) mat_mul(res, res, bufa, n, n, n);
		mat_mul(bufa, bufa, bufa, n, n, n);
		x >>= 1;
	}
}
int n, m, t;
int init[MAXN][MAXN], b[MAXN][MAXN], trans[MAXN][MAXN];
int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%d%d", &n, &m, &t);
		for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) {
			scanf("%d", &init[0][i * n + j]);
			init[0][i * n + j] = (init[0][i * n + j] & 1);
		}
		for(int i = 0; i < m; i++) for(int j = 0; j < m; j++) {
			scanf("%d", &b[i][j]);
			b[i][j] = (b[i][j] & 1);
		}
		memset(trans, 0, sizeof(trans));
		for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) {
			for(int p = i - m; p <= i + m; p++) for(int q = j - m; q <= j + m; q++) {
				if(0 <= p && p < n && 0 <= q && q < n) {
					int pp = p - i + m / 2;
					int qq = q - j + m / 2;
					if(0 <= pp && pp < m && 0 <= qq && qq < m) {
						trans[p * n + q][i * n + j] = b[pp][qq];
					}
				}
			}
		}
		n *= n;
		mat_pow(trans, trans, t, n);
		mat_mul(init, init, trans, 1, n, n);
		int ans = 0;
		for(int i = 0; i < n; i++) if(init[0][i]) ans++;
		printf("%d\n", ans);
	}
	return 0;
}