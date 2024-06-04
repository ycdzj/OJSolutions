#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN = 505;

char str[MAXN];
int n;
int f[MAXN][MAXN];
int main() {
    scanf("%d%s", &n, str);
    for(int l = n - 1; l >= 0; l--) {
        for(int r = l; r < n; r++) {
            f[l][r] = 1 + f[l + 1][r];
            for(int i = l + 1; i <= r; i++) {
                if(str[i] == str[l]) {
                    f[l][r] = min(f[l][r], f[l + 1][i - 1] + f[i][r]);
                }
            }
        }
    }
    printf("%d\n", f[0][n - 1]);
    return 0;
}