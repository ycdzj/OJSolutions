#include <cstdio>

const int MAXN = 1e5 + 5;

int main() {
    long long n, m, k;
    scanf("%lld%lld%lld", &n, &m, &k);
    long long pos = 0, pospage = 0, cnt = 0;
    long long ans = 0;
    for(int i = 0; i < m; i++) {
        long long p;
        scanf("%lld", &p);
        p--;

        long long len = p - pos;
        pos += len;
        pospage += len;
        if(pospage >= k) {
            pospage -= cnt;
            pospage %= k;
            if(cnt > 0) {
                ans++;
                cnt = 0;
            }
        }

        pos++;
        pospage++;
        cnt++;
        if(pospage >= k) {
            pospage -= cnt;
            pospage %= k;
            if(cnt > 0) {
                ans++;
                cnt = 0;
            }
        }
    }
    if(cnt > 0) {
        ans++;
    }
    printf("%lld\n", ans);
    return 0;
}
