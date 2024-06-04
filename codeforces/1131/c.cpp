#include <cstdio>
#include <algorithm>
const int MAXN = 105;
int a[MAXN], n;
int main() {
    scanf("%d", &n);
    for(int i = 0; i < n; i++) scanf("%d", &a[i]);
    std::sort(a, a + n);
    for(int i = 0; i < n; i += 2) printf("%d ", a[i]);
    for(int i = n - 1; i >= 1; i -= 2) {
        if(i % 2 == 0) i--;
        printf("%d ", a[i]);
    }
    return 0;
}
