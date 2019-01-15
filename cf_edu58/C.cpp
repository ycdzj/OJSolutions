#include <cstdio>
#include <algorithm>
#include <set>
using namespace std;
const int MAXN = 1e5 + 5;
struct Interval {
    int l, r, id, mask;
} interval[MAXN];
bool cmp(const Interval &x, const Interval &y) {
    if(x.l != y.l) return x.l < y.l;
    return x. r < y.r;
}
bool cmp2(const Interval &x, const Interval &y) {
    return x.id < y.id;
}
int n;
int main() {
    int T; scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        for(int i = 0; i < n; i++) {
            scanf("%d%d", &interval[i].l, &interval[i].r);
            interval[i].id = i;
        }
        sort(interval, interval + n, cmp);
        int max_ = interval[0].r;
        int ans = -1;
        for(int i = 1; i < n; i++) {
            if(max_ < interval[i].l) {
                ans = i;
                break;
            }
            max_ = max(max_, interval[i].r);
        }
        if(ans == -1) printf("-1\n");
        else {
            for(int i = 0; i < ans; i++) interval[i].mask = 1;
            for(int i = ans; i < n; i++) interval[i].mask = 2;
            sort(interval, interval + n, cmp2);
            for(int i = 0; i < n; i++) printf("%d ", interval[i].mask);
            printf("\n");
        }
    }
    return 0;
}