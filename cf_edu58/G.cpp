#include <cstdio>
int bas[30];
void insert(int x) {
    for(int i = 29; i >= 0; i--) if(x >> i & 1) {
        if(bas[i]) x ^= bas[i];
        else {
            bas[i] = x;
            return;
        }
    }
}
int n;
int main() {
    scanf("%d", &n);
    int sum = 0;
    for(int i = 0; i < n; i++) {
        int a; scanf("%d", &a);
        sum ^= a;
        insert(sum);
    }
    if(sum == 0) printf("-1\n");
    else {
        int ans = 0;
        for(int i = 0; i < 30; i++) if(bas[i]) ans++;
        printf("%d\n", ans);
    }
    return 0;
}