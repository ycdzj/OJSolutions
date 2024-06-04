#include <cstdio>
#include <cmath>
const int MAXN = 1005;
int n;
long long a[MAXN][MAXN];
long long mysqrt(long long x) {
    long long y = sqrt(x);
    for(int i = -1; i <= 1; i++) {
        if((y + i) * (y + i) == x) {
            return y + i;
        }
    }
    return -1;
}
int main() {
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            scanf("%lld", &a[i][j]);
        }
    }

    long long a0 = (long long)a[0][1] * a[0][2] / a[1][2];
    a[0][0] = a0;
    a0 = mysqrt(a0);
    for(int i = 0; i < n; i++) {
        printf("%lld ", a[0][i] / a0);
    }
    printf("\n");
    return 0;
}
