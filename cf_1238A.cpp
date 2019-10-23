#include <cstdio>

int main() {
    int t;
    scanf("%d", &t);
    while(t--) {
        long long x, y;
        scanf("%lld%lld", &x, &y);
        if(x - 1 == y) {
            printf("No\n");
        }
        else {
            printf("Yes\n");
        }
    }
    return 0;
}
