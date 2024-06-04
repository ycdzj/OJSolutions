#include <vector>
#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN = 2005;

int n, m;
int a[MAXN], b[MAXN];
int c[MAXN], d[MAXN];

struct Item {
    int idx;
    int val[2];
} item[MAXN * MAXN], item2[MAXN * MAXN];
int cnt[MAXN * MAXN], cnt_item;
int max_val[MAXN * MAXN];

bool cmp_1(Item a, Item b) {
    return a.val[0] < b.val[0];
}

bool cmp_2(Item a, Item b) {
    return a.val[1] < b.val[1];
}

bool check(int x) {
    fill(cnt, cnt + cnt_item, 1);
    int cur = cnt_item;
    int pos_1 = 0, pos_2 = cnt_item;
    for(int i = 0; i <= x; i++) {
        while(pos_1 < cnt_item && item[pos_1].val[0] <= i) {
            if(cnt[item[pos_1].idx]++ == 0) {
                cur++;
            }
            pos_1++;
        }
        while(pos_2 > 0 && item2[pos_2 - 1].val[1] > x - i) {
            if(--cnt[item2[pos_2 - 1].idx] == 0) {
                cur--;
            }
            pos_2--;
        }
        if(cur == cnt_item) {
            return true;
        }
    }
    return false;
}

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 0; i < n; i++) {
        scanf("%d%d", &a[i], &b[i]);
    }
    for(int i = 0; i < m; i++) {
        scanf("%d%d", &c[i], &d[i]);
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(a[i] <= c[j] && b[i] <= d[j]) {
                int x = c[j] - a[i] + 1;
                int y = d[j] - b[i] + 1;
                max_val[x] = max(max_val[x], y);
            }
        }
    }
    for(int i = 1; i <= 1000001; i++) {
        if(max_val[i] != 0) {
            item[cnt_item].idx = cnt_item;
            item[cnt_item].val[0] = i;
            item[cnt_item].val[1] = max_val[i];
            item2[cnt_item] = item[cnt_item];
            cnt_item++;
        }
    }
    sort(item, item + cnt_item, cmp_1);
    sort(item2, item2 + cnt_item, cmp_2);
    int left = 0, right = 1000005;
    while(left < right) {
        int mid = (right - left) / 2 + left;
        if(check(mid)) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    printf("%d\n", left);
    return 0;
}