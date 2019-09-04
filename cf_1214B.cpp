#include <cstdio>
#include <algorithm>
using namespace std;
int main() {
    int b, g, n;
    scanf("%d%d%d", &b, &g, &n);
    int l = max(0, n - g);
    int r = min(n, b);
    printf("%d\n", r - l + 1);
    return 0;
}