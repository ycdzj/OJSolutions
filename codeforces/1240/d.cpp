#include <cstdio>
#include <map>
using namespace std;

const int MAXN = 3e5 + 5;

int n, a[MAXN], nxt[MAXN], g[MAXN];
map<int, int> f[MAXN];

int main() {
    int q;
    scanf("%d", &q);
    while(q--) {
        scanf("%d", &n);
        for(int i = 1; i <= n; i++) {
            scanf("%d", &a[i]);
            f[i].clear();
            nxt[i] = 0;
        }
        f[n][a[n]] = n;
        for(int i = n - 1; i >= 1; i--) {
            if(f[i + 1].count(a[i])) {
                nxt[i] = f[i + 1][a[i]];
                if(nxt[i] <= n - 1) {
                    swap(f[i], f[nxt[i] + 1]);
                }
            }
            f[i][a[i]] = i;
        }
        long long ans = 0;
        for(int i = n; i >= 1; i--) {
            if(nxt[i] == 0) {
                g[i] = 0;
            }
            else {
                g[i] = 1;
                if(nxt[i] <= n - 1) {
                    g[i] += g[nxt[i] + 1];
                }
            }
            ans += g[i];
        }
        printf("%lld\n", ans);
    }
    return 0;
}
