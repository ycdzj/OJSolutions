#include <cstdio>

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int n;
        scanf("%d", &n);

        int pre;
        scanf("%d", &pre);
        bool ans = false;
        for (int i = 1; i < n; i++) {
            int cur;
            scanf("%d", &cur);
            if (pre <= cur) {
                ans = true;
            }
            pre = cur;
        }

        if (ans) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }
    return 0;
}
