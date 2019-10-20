#include <cstdio>
#include <cstring>

const int MAXN = 1e5 + 5;

int cnt[MAXN];

int main() {
    int T;
    int cnt_case = 0;
    scanf("%d", &T);
    while(T--) {
        int n, m, q;
        scanf("%d%d%d", &n, &m, &q);
        memset(cnt, 0, sizeof(cnt));
        for(int i = 0; i < m; i++) {
            int val;
            scanf("%d", &val);
            for(int x = 1; x <= val / x; x++) {
                if(val % x == 0) {
                    cnt[x]++;
                    if(x != val / x) {
                        cnt[val / x]++;
                    }
                }
            }
        }
        long long ans = 0;
        while(q--) {
            int x;
            scanf("%d", &x);
            ans += n / x - cnt[x];
        }
        printf("Case #%d: %lld\n", ++cnt_case, ans);
    }
    return 0;
}
