#include <cstdio>

const int MAXN = 2e5 + 5;

int n, k;
char str[MAXN];

int main() {
    int t;
    scanf("%d", &t);
    for(int i_case = 1; i_case <= t; i_case++) {
        scanf("%d%d", &n, &k);
        scanf("%s", str);
        int cnt = 0;
        for(int i = 0; i < n / 2; i++) {
            if(str[i] != str[n - 1 - i]) {
                cnt++;
            }
        }

        int ans = cnt - k;
        if(ans < 0) {
            ans = -ans;
        }

        printf("Case #%d: %d\n", i_case, ans);
    }
    return 0;
}