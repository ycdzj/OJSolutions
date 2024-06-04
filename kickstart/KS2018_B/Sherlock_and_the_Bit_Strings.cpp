#include <cstdio>
#include <vector>
using namespace std;

typedef long long ll;
const int MAXN = 105;
const ll INF = 1e18;

int n, k;
ll p;
vector<pair<int, int>> lim[MAXN];
ll f[MAXN][1 << 15];
int sum[MAXN][1 << 15];
inline int append(int mask, int val) {
    return (mask << 1 | val) & ((1 << 15) - 1);
}
int main() {
    for(int j = 0; j < (1 << 15); j++) {
        for(int i = 1; i <= 15; i++) {
            sum[i][j] = sum[i - 1][j] + (j >> (i - 1) & 1);
        }
    }
    int T;
    scanf("%d", &T);
    for(int cnt_case = 1; cnt_case <= T; cnt_case++) {
        scanf("%d%d%lld", &n, &k, &p);
        for(int i = 1; i <= n + 1; i++) lim[i].clear();
        for(int i = 0; i < k; i++) {
            int a, b, c; scanf("%d%d%d", &a, &b, &c);
            lim[b].push_back({b - a, c});
        }
        for(int j = 0; j < (1 << 15); j++) f[n + 1][j] = 1;
        for(int i = n; i >= 1; i--) {
            for(int j = 0; j < (1 << 15); j++) {
                bool flag_0 = true, flag_1 = true;
                for(auto pr : lim[i]) {
                    if(sum[pr.first][j] != pr.second) flag_0 = false;
                    if(sum[pr.first][j] + 1 != pr.second) flag_1 = false;
                }
                f[i][j] = 0;
                if(flag_0) {
                    f[i][j] += f[i + 1][append(j, 0)];
                }
                if(flag_1) {
                    f[i][j] += f[i + 1][append(j, 1)];
                }
                if(f[i][j] > INF) f[i][j] = INF;
            }
        }
        printf("Case #%d: ", cnt_case);
        for(int cur = 0, i = 1; i <= n; i++) {
            bool flag_0 = true;
            for(auto pr : lim[i]) {
                if(sum[pr.first][cur] != pr.second) flag_0 = false;
            }
            if(flag_0 && p <= f[i + 1][append(cur, 0)]) {
                printf("0");
                cur = append(cur, 0);
            }
            else {
                printf("1");
                if(flag_0) {
                    p -= f[i + 1][append(cur, 0)];
                }
                cur = append(cur, 1);
            }
        }
        printf("\n");
    }
    return 0;
}