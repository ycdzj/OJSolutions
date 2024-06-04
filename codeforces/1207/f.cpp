#include <cstdio>
using namespace std;

const int MAXN = 5e5 + 5;
const int N = 5e5;
const int M = 500;

int v[M][M];
int a[MAXN];

int main() {
    int q;
    scanf("%d", &q);
    while(q--) {
        int t, x, y;
        scanf("%d%d%d", &t, &x, &y);
        if(t == 1) {
            a[x] += y;
            for(int i = 1; i < M; i++) {
                v[i][x % i] += y;
            }
        }
        else {
            if(x < M) {
                printf("%d\n", v[x][y]);
            }
            else {
                int ans = 0;
                for(int i = y; i <= N; i += x) {
                    ans += a[i];
                }
                printf("%d\n", ans);
            }
        }
    }
    return 0;
}
