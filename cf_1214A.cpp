#include <cstdio>
#include <algorithm>
using namespace std;
int main() {
    int n, d, e;
    scanf("%d%d%d", &n, &d, &e);
    e *= 5;
    int ans = n;
    for(int x = 0; x <= n; x += d) {
        int rem = n - x;
        ans = min(ans, rem % e);
    }
    printf("%d\n", ans);
    return 0;
}