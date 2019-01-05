#include <cstdio>

int main() {
    int T; scanf("%d", &T);
    while(T--) {
        int ang; scanf("%d", &ang);
        int ans;
        for(ans = 1; ans <= 360; ans++) {
            if((ang * ans) % 180 == 0 && (ang * ans) / 180 <= ans - 2) {
                break;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
