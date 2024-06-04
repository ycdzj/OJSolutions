#include <cstdio>

int main() {
    int n;
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            int cur = j * n + i;
            if(j & 1) {
                cur = j * n + n - 1 - i;
            }
            printf("%d ", cur + 1);
        }
        printf("\n");
    }
    return 0;
}
