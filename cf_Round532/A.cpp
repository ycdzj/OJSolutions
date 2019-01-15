#include <cstdio>
#include <algorithm>
using namespace std;
const int MAXN = 106;
int n, k;
int cnt0[MAXN], cnt1[MAXN];
int tot0, tot1;
inline int abs(int x) { return x < 0 ? -x : x; }
int main() {
    scanf("%d%d", &n, &k);
    for(int i = 0; i < n; i++) {
        int t; scanf("%d", &t);
        if(t == 1) {
            cnt0[i % k]++;
            tot0++;
        }
        else {
            cnt1[i % k]++;
            tot1++;
        }
    }
    int ans = 0;
    for(int i = 0; i < k; i++) {
        int cur0 = tot0 - cnt0[i];
        int cur1 = tot1 - cnt1[i];
        ans = max(ans, abs(cur0 - cur1));
    }
    printf("%d\n", ans);
    return 0;
}