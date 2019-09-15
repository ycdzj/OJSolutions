#include <cstdio>
#include <algorithm>
using namespace std;

struct Item {
    int val, jdx;
    bool operator < (const Item &item) const {
        return val > item.val;
    }
};

int n, m, a[13][2005];
int f[1 << 12][13], g[1 << 12][13];
Item item[13 * 2005];
bool vis[2005];

int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &n, &m);
        int cnt_item = 0;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                scanf("%d", &a[i][j]);
                item[cnt_item++] = {a[i][j], j};
                vis[j] = false;
            }
        }
        sort(item, item + cnt_item);
        for(int i = 0, cnt_vis = 0; cnt_vis < n && i < cnt_item; i++) {
            if(!vis[item[i].jdx]) {
                vis[item[i].jdx] = true;
                cnt_vis++;
            }
        }
        int new_m = 0;
        for(int j = 0; j < m; j++) {
            if(vis[j]) {
                for(int i = 0; i < n; i++) {
                    a[i][new_m] = a[i][j];
                }
                new_m++;
            }
        }
        m = new_m;
        int mask = (1 << n);
        for(int i = 0; i < mask; i++) {
            f[i][m] = 0;
        }
        for(int i = 0; i < mask; i++) {
            for(int j = 0; j < m; j++) {
                g[i][j] = 0;
                for(int s = 0; s < n; s++) {
                    int cur = 0;
                    for(int x = 0; x < n; x++) {
                        if(i >> x & 1) {
                            cur += a[(x + s) % n][j];
                        }
                    }
                    g[i][j] = max(g[i][j], cur);
                }
            }
        }
        for(int j = m - 1; j >= 0; j--) {
            for(int i = 0; i < mask; i++) {
                f[i][j] = g[i][j];
                for(int k = i; k; k = ((k - 1) & i)) {
                    int dif = (k ^ i);
                    f[i][j] = max(f[i][j], g[dif][j] + f[k][j + 1]);
                }
            }
        }
        printf("%d\n", f[mask - 1][0]);
    }
    return 0;
}
