#include <cstdio>

const int MAXN = 2e5 + 5;

int h, n;
int a[MAXN];

int main() {
    int q;
    scanf("%d", &q);
    while(q--) {
        scanf("%d%d", &h, &n);
        for(int i = 0; i < n; i++) {
            scanf("%d", &a[i]);
        }
        int ans = 0, i = 1;
        for(; i < n - 1; i++) {
            if(a[i + 1] != a[i] - 1) {
                ans++;
            }
            else {
                i++;
            }
        }
        if(i == n - 1 && a[n - 1] >= 2) {
            ans++;
        }
        printf("%d\n", ans);
    }
    return 0;
}
