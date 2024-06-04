#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN = 505;
const int INF = 1e9 + 8;

int a[MAXN], n;
int f[MAXN][MAXN];
int g[MAXN];

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		f[i][i] = a[i];
	}
	for(int l = 2; l <= n; l++) {
		for(int i = 1; i <= n; i++) {
			int j = i + l - 1;
			if(j > n) {
				break;
			}

			for(int k = i; k < j; k++) {
				if(f[i][k] == f[k + 1][j] && f[i][k] != 0) {
					f[i][j] = f[i][k] + 1;
					break;
				}
			}
		}
	}
	for(int i = n; i >= 1; i--) {
		g[i] = INF;
		for(int j = i; j <= n; j++) {
			if(f[i][j] != 0) {
				g[i] = min(g[i], 1 + g[j + 1]);
			}
		}
	}
	printf("%d\n", g[1]);
	return 0;
}
