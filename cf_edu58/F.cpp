#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
const int MAXN = 405;
int n, m;
ll a[MAXN];
ll f[MAXN][MAXN][2];
struct Truck {
    int s, f, c;
};
vector<Truck> truck[MAXN];
int main() {
    scanf("%d%d", &n, &m);
    for(int i = 0; i < n; i++) scanf("%lld", &a[i]);
    for(int i = 0; i < m; i++) {
        int s, f, c, r; scanf("%d%d%d%d", &s, &f, &c, &r);
        truck[r].push_back({s - 1, f - 1, c});
    }
    ll ans = 0;
    int cur = 0, pre = 1;
    for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) {
        if(i <= j) f[i][j][cur] = a[j] - a[i];
        else f[i][j][cur] = a[i] - a[j];
    }
    for(int k = 0; k <= n; k++) {
        for(auto &val : truck[k]) {
            ans = max(ans, val.c * f[val.s][val.f][cur]);
        }
        cur ^= 1; pre ^= 1;
        for(int j = 0; j < n; j++) {
            int x = j;
            for(int i = j; i >= 0; i--) {
                while(i <= x - 1) {
                    ll lval = max(a[x - 1] - a[i], f[x - 1][j][pre]);
                    ll rval = max(a[x] - a[i], f[x][j][pre]);
                    if(lval < rval) {
                        x--;
                    }
                    else {
                        break;
                    }
                }
                f[i][j][cur] = max(a[x] - a[i], f[x][j][pre]);
            }
            x = j;
            for(int i = j; i < n; i++) {
                while(x + 1 <= i) {
                    ll lval = max(a[i] - a[x], f[x][j][pre]);
                    ll rval = max(a[i] - a[x + 1], f[x + 1][j][pre]);
                    if(lval > rval) {
                        x++;
                    }
                    else {
                        break;
                    }
                }
                f[i][j][cur] = max(a[i] - a[x], f[x][j][pre]);
            }
        }
    }
    printf("%lld\n", ans);
    return 0;
}