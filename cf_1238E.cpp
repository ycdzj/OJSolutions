#include <cstdio>
#include <algorithm>
using namespace std;

const int INF = 1e9;
const int MAXN = 1e5 + 5;
const int MAXM = 20;

int n, m;
char str[MAXN];
int f[1 << MAXM];
int pr[MAXM][MAXM];
int pr_sum[1 << MAXM];

int main() {
    scanf("%d%d", &n, &m);
    scanf("%s", str);
    for(int i = 1; i < n; i++) {
        int x = str[i] - 'a';
        int y = str[i - 1] - 'a';
        pr[x][y]++;
        pr[y][x]++;
    }
    for(int i = 0; i < m; i++) {
        pr[i][i] = 0;
    }
    int mask = (1 << m);
    for(int i = 1; i < mask; i++) {
        for(int j = 0; j < m; j++) {
            if(i >> j & 1) {
                pr_sum[i] = pr_sum[i ^ (1 << j)];
                for(int k = 0; k < m; k++) {
                    if(i >> k & 1) {
                        pr_sum[i] -= pr[j][k];
                    }
                    else {
                        pr_sum[i] += pr[j][k];
                    }
                }
                break;
            }
        }
    }
    for(int i = 1; i < mask; i++) {
        f[i] = INF;
        for(int j = 0; j < m; j++) {
            if(i >> j & 1) {
                f[i] = min(f[i], f[i ^ (1 << j)] + pr_sum[i ^ (1 << j)]);
            }
        }
    }
    printf("%d\n", f[mask - 1]);
    return 0;
}
