#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN = 1e5 + 5;
const long long INF = 1e18;

int n, m;
int cnt[MAXN];
struct Item {
    int val, idx, rank;
    bool vis;
} item[MAXN];
int idx[MAXN];
bool cmp1(Item a, Item b) {
    return a.val > b.val;
}
bool cmp2(int a, int b) {
    return item[a].rank < item[b].rank;
}

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 0; i < m; i++) {
        scanf("%d%d", &item[i].val, &item[i].idx);
        idx[i] = i;
    }
    sort(item, item + m, cmp1);
    for(int i = 0; i < m; i++) item[i].rank = cnt[item[i].idx]++;
    sort(idx, idx + m, cmp2);

    int cur = 0, p = m - 1, q = 0;
    long long ans, curans = 0;
    for(int i = 0; i < m; i++) {
        curans += item[i].val;
        item[i].vis = true;
        cur++;
    }
    ans = curans;
    for(int k = m - 1; k >= 0; k--) {
        while(p >= 0 && item[idx[p]].rank >= k) {
            if(!item[idx[p]].vis) {
                item[idx[p]].vis = true;
                curans += item[idx[p]].val;
                cur++;
            }
            p--;
        }
        for(; cur > k + 1 && q < m; q++) {
            if(item[q].rank >= k) continue;
            item[q].vis = false;
            curans -= item[q].val;
            cur--;
        }
        ans = min(ans, curans);
    }
    printf("%lld\n", ans);
    return 0;
}