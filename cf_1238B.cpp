#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN = 1e5 + 5;

int a[MAXN], n, r;

int main() {
    int q;
    scanf("%d", &q);
    while(q--) {
        scanf("%d%d", &n, &r);
        for(int i = 0; i < n; i++) {
            scanf("%d", &a[i]);
        }
        sort(a, a + n);
        n = unique(a, a + n) - a;
        long long ans = 0;
        for(int i = n - 1; i >= 0; i--) {
            if(a[i] - ans * r <= 0) {
                continue;
            }
            else {
                ans++;
            }
        }
        printf("%lld\n", ans);
    }
    return 0;
}
