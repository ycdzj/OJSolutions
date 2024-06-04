#include <cstdio>

int n;
char str[105];
bool on[105];
int a[105], b[105];

int main() {
    scanf("%d", &n);
    scanf("%s", str);
    for(int i = 0; i < n; i++) {
        scanf("%d%d", &a[i], &b[i]);
    }
    int ans = 0;
    for(int t = 0; t <= 100000; t++) {
        int cur = 0;
        for(int i = 0; i < n; i++) {
            bool flag = (str[i] == '1');
            if(t >= b[i]) {
                int x = (t - b[i]) / a[i] + 1;
                if(x & 1) {
                    flag = !flag;
                }
            }
            if(flag) {
                cur++;
            }
        }
        if(ans < cur) {
            ans = cur;
        }
    }
    printf("%d\n", ans);
    return 0;
}
