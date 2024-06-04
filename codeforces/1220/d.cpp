#include <cstdio>

int calc(long long x) {
    if(x == 0) {
        return -1;
    }
    int res = 0;
    while((x & 1) == 0) {
        res++;
        x >>= 1;
    }
    return res;
}

const int MAXN = 2e5 + 5;

int n;
long long a[MAXN];
int cnt[65];

int main() {
    scanf("%d", &n);
    int imax = 0;
    for(int i = 0; i < n; i++) {
        scanf("%lld", &a[i]);
        int cur = calc(a[i]);
        if(++cnt[cur] > cnt[imax]) {
            imax = cur;
        }
    }
    printf("%d\n", n - cnt[imax]);
    for(int i = 0; i < n; i++) {
        if(calc(a[i]) != imax) {
            printf("%lld ", a[i]);
        }
    }
    printf("\n");
    return 0;
}
