#include <cstdio>
#include <algorithm>
const int MAXN = 1e5 + 5;
int a[2][MAXN], n;
int main() {
    scanf("%d", &n);
    for(int i = 0; i < n; i++) scanf("%d", &a[0][i]);
    for(int i = 0; i < n; i++) scanf("%d", &a[1][i]);
    std::sort(a[0], a[0] + n);
    std::sort(a[1], a[1] + n);
    int p[2] = {n - 1, n - 1};
    long long sum[2] = {0, 0};
    for(int cur = 0; true; cur ^= 1) {
        if(p[0] == -1 && p[1] == -1) break;
        if(p[cur] == -1) p[cur ^ 1]--;
        else {
            if(p[cur ^ 1] == -1 || a[cur ^ 1][p[cur ^ 1]] < a[cur][p[cur]]) sum[cur] += a[cur][p[cur]--];
            else p[cur ^ 1]--;
        }
    }
    printf("%lld\n", sum[0] - sum[1]);
    return 0;
}