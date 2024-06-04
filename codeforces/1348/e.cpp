#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN = 505;

int n, k;
int a[MAXN], b[MAXN];
bool f[MAXN][MAXN];

int main() {
    scanf("%d%d", &n, &k);
    long long sum_a = 0, sum_b = 0;
    for(int i = 1; i <= n; i++) {
        scanf("%d%d", &a[i], &b[i]);
        sum_a += a[i];
        sum_b += b[i];
    }
    f[0][0] = true;
    for(int i = 1; i <= n; i++) {
        for(int j = 0; j < k; j++) {
            f[i][j] = f[i - 1][j];
            for(int x = 0; x <= k; x++) {
                if(x <= a[i] && (k - x) <= b[i]) {
                    f[i][j] = f[i][j] || f[i - 1][(j + k - x) % k];
                }
            }
        }
    }
    long long ans = sum_a / k + sum_b / k;
    for(int x = 1; x < k; x++) {
        if(f[n][x]) {
            ans = max(ans, (sum_a - x) / k + (sum_b - (k - x)) / k + 1);
        }
    }
    printf("%lld\n", ans);
    return 0;
}




