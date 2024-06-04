#include <cstdio>
#include <vector>
using namespace std;

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int n;
        scanf("%d", &n);
        vector<int> count(31);
        for (int i = 0; i < n; i++) {
            int a;
            scanf("%d", &a);
            for (int j = 30; j >= 0; j--) {
                if (a >> j & 1) {
                    count[j]++;
                    break;
                }
            }
        }
        long long ans = 0;
        for (int x : count) {
            ans += (long long)x * (x - 1) / 2;
        }
        printf("%lld\n", ans);
    }
    return 0;
}
