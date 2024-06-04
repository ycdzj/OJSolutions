#include <cstdio>
#include <algorithm>
const int MAXN = 2e4 + 5;
int v[MAXN], n, k;
long long s[MAXN];
int main() {
    int T; scanf("%d", &T);
    for(int cnt_case = 1; cnt_case <= T; cnt_case++) {
        scanf("%d%d", &n, &k);
        for(int i = 0; i < n; i++) scanf("%d", &v[i]);
        std::sort(v, v + n);
        s[n] = 0;
        for(int i = n - 1; i >= 0; i--) s[i] = s[i + 1] + v[i];
        double cur = 0;
        for(int i = 0; i < k + 1; i++) {
            int cnt = std::lower_bound(v, v + n, cur) - v;
            cur = ((cur * cnt) + s[cnt]) / (double)n;
        }
        printf("Case #%d: %.6f\n", cnt_case, cur);
    }
    return 0;
}
