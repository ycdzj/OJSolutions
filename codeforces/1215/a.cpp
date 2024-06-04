#include <cstdio>
#include <algorithm>
using namespace std;

int get_min(int a1, int a2, int k1, int k2, int n) {
    n -= a1 * (k1 - 1);
    n -= a2 * (k2 - 1);
    n = max(0, n);
    n = min(a1 + a2, n);
    return n;
}
int get_max(int a1, int a2, int k1, int k2, int n) {
    int cnt1 = min(n / k1, a1);
    n -= cnt1 * k1;
    int cnt2 = min(n / k2, a2);
    return cnt1 + cnt2;
}

int main() {
    int a1, a2, k1, k2, n;
    scanf("%d%d%d%d%d", &a1, &a2, &k1, &k2, &n);
    if(k1 > k2) {
        swap(k1, k2);
        swap(a1, a2);
    }
    printf("%d %d\n", get_min(a1, a2, k1, k2, n), get_max(a1, a2, k1, k2, n));
    return 0;
}
