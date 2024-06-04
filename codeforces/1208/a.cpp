#include <cstdio>

int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        int a, b, n;
        scanf("%d%d%d", &a, &b, &n);
        int arr[3] = {a, b, a ^ b};
        printf("%d\n", arr[n % 3]);
    }
    return 0;
}