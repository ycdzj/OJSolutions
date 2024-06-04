#include <cstdio>

const int MOD = 1e9 + 7;
const int MAXN = 3005;

inline int addmod(int a, int b) { return (a + b) % MOD; }

int n, m;
int f[MAXN][MAXN][2];

inline int get(int i, int j, int k) {
    if(0 <= j && j <= n) {
        return f[i][j][k];
    }
    return 0;
}

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++) f[0][i][0] = 1;
    f[0][0][1] = 1;
    for(int i = 1; i <= m; i++) {
        for(int j = 0; j <= n; j++) {
            int a = get(i - 1, j + 1, 0);
            int b = get(i - 1, j, 0);
            int c = get(i - 1, j - 1, 0);

            int x = get(i - 1, j + 1, 1);
            int y = get(i - 1, j, 1);
            int z = get(i - 1, j - 1, 1);

            if(j != 0) {
                f[i][j][0] = addmod(f[i][j][0], a);
                f[i][j][0] = addmod(f[i][j][0], c);
                if(j != n) {
                    f[i][j][0] = addmod(f[i][j][0], b);
                }
                if(j != 1) {
                    f[i][j][0] = addmod(f[i][j][0], b);
                }
            }

            f[i][j][1] = addmod(f[i][j][1], x);
            f[i][j][1] = addmod(f[i][j][1], z);
            if(j != n) {
                f[i][j][1] = addmod(f[i][j][1], y);
            }
            if(j != 0) {
                f[i][j][1] = addmod(f[i][j][1], y);
            }
            if(j == 0) {
                f[i][j][1] = addmod(f[i][j][1], a);
                f[i][j][1] = addmod(f[i][j][1], c);
                f[i][j][1] = addmod(f[i][j][1], b);
            }
            if(j == 1) {
                f[i][j][1] = addmod(f[i][j][1], b);
            }

        }
    }
    int ans = 0;
    for(int j = 0; j <= n; j++) ans = addmod(ans, f[m][j][1]);
    printf("%d\n", ans);
    return 0;
}
