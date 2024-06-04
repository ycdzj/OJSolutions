#include <cstdio>
const int MOD = 1e9 + 7;
const int MAXN = 40;
typedef long long ll;
void mat_mul(int res[][MAXN], int a[][MAXN], int b[][MAXN], int n, int m, int k) {
	static int tmp[MAXN][MAXN];
	for(int i = 0; i < n; i++) for(int j = 0; j < k; j++) {
		long long sum = 0;
		for(int x = 0; x < m; x++) sum += ((long long)a[i][x] * b[x][j]) % MOD;
		tmp[i][j] = sum % MOD;
	}
	for(int i = 0; i < n; i++) for(int j = 0; j < k; j++) res[i][j] = tmp[i][j];
}
void mat_pow(int res[][MAXN], int a[][MAXN], int x, int n) {
	static int cur[MAXN][MAXN];
	for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) cur[i][j] = a[i][j];
	for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) res[i][j] = (i == j) ? 1 : 0;
	while(x) {
		if(x & 1) mat_mul(res, res, cur, n, n, n);
		mat_mul(cur, cur, cur, n, n, n);
		x >>= 1;
	}
}
int n, m;
int trans[MAXN][MAXN];
int main() {
	scanf("%d%d", &m, &n);
	int exp = (1 << n);
	for(int i = 0; i < exp; i++) for(int j = 0; j < exp; j++) {
		if(i & j) continue;
		int k = (i ^ j);
		bool flag = true;
		for(int x = 0; x < n; x++) if(!(k >> x & 1)) {
			if(x == n - 1 || (k >> (x + 1) & 1)) flag = false;
			else x++;
		}
		if(flag) trans[i][j] = 1;
	}
	mat_pow(trans, trans, m, exp);
	printf("%d\n", trans[0][0]);
	return 0;
}