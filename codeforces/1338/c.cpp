#include <cstdio>

const int MAXN = 1e7;

int f[4][3] = {
        {0, 0, 0},
        {1, 2, 3},
        {2, 3, 1},
        {3, 1, 2}
};

long long solve(long long n) {
    for (int i = 1; i <= 60; i++) {
        long long cnt = 3 * ((long long) 1 << (2 * (i - 1)));
        if (n >= cnt) {
            n -= cnt;
            continue;
        }
        long long m = n / 3;
        long long k = n % 3;
        long long ans = f[1][k];
        for(int j = 2 * (i - 2); j >= 0; j -= 2) {
            long long cur = (m >> j & 3);
            ans = ((ans << 2) | f[cur][k]);
        }
        return ans;
    }
    return -1;
}

int main() {
    int t;
    scanf("%d", &t);
    while(t-- > 0) {
        long long n;
        scanf("%lld", &n);
        printf("%lld\n", solve(n - 1));
    }
    return 0;
}