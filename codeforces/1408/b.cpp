#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int t;
    scanf("%d", &t);
    while(t--) {
        int n, k;
        scanf("%d%d", &n, &k);
        vector<int> a(n);
        for(int i = 0; i < n; i++) {
            scanf("%d", &a[i]);
        }
        int m = unique(a.begin(), a.end()) - a.begin();
        int ans = 1;
        if (m > k) {
            if(k <= 1) {
                ans = -1;
            } else {
                ans += (m - k) / (k - 1);
                if((m - k) % (k - 1) != 0) {
                    ans++;
                }
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}