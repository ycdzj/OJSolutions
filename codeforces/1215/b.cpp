#include <cstdio>

int n;

int main() {
    scanf("%d", &n);
    long long f = 0, g = 0, ans_f = 0, ans_g = 0;
    for(int i = 0; i < n; i++) {
        int a;
        scanf("%d", &a);
        long long nxt_f, nxt_g;
        if(a < 0) {
            nxt_f = g;
            nxt_g = 1 + f;
        }
        else {
            nxt_f = 1 + f;
            nxt_g = g;
        }
        f = nxt_f;
        g = nxt_g;

        ans_f += f;
        ans_g += g;
    }
    printf("%lld %lld\n", ans_g, ans_f);
    return 0;
}
