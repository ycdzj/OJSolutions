#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN = 2e5 + 5;
const long long INF = 1e18;

struct Item {
    int val, idx;
};
bool cmp(Item a, Item b) {
    return a.val < b.val;
}

int n, m;
Item a[MAXN], b[MAXN];
int ans[MAXN];

long long sum[MAXN];
void change(int l, int r, int val) {
    l = (l % n + n) % n;
    r = (r % n + n) % n;
    if(l < r) {
        sum[l] += val;
        sum[r] -= val;
    }
    else {
        sum[l] += val;
        sum[0] += val;
        sum[r] -= val;
    }
}
void revchange(int l, int r, int val) {
    change(r + 1, l + 1, val);
}

int main() {
    scanf("%d%d", &m, &n);
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i].val);
        a[i].idx = i + 1;
    }
    for(int i = 0; i < n; i++) {
        scanf("%d", &b[i].val);
        b[i].idx = i + 1;
    }
    sort(a, a + n, cmp);
    sort(b, b + n, cmp);
    for(int i = 0, l1 = 0, l2 = 0, l3 = 0; i < n; i++) {
        while(l1 < n && b[l1].val < a[i].val - m / 2) l1++;
        while(l2 < n && b[l2].val < a[i].val) l2++;
        while(l3 < n && b[l3].val < a[i].val + (m + 1) / 2) l3++;
        if(0 < l1) {
            change(-i, l1 - i, -a[i].val + m);
        }
        if(l1 < l2) {
            change(l1 - i, l2 - i, a[i].val);
        }
        if(l2 < l3) {
            change(l2 - i, l3 - i, -a[i].val);
        }
        if(l3 < n) {
            change(l3 - i, n - i, a[i].val + m);
        }
    }
    for(int j = 0, l1 = 0, l2 = 0, l3 = 0; j < n; j++) {
        while(l1 < n && a[l1].val <= b[j].val - (m + 1) / 2) l1++;
        while(l2 < n && a[l2].val <= b[j].val) l2++;
        while(l3 < n && a[l3].val <= b[j].val + m / 2) l3++;
        if(0 < l1) {
            revchange(j, j - l1, -b[j].val);
        }
        if(l1 < l2) {
            revchange(j - l1, j - l2, b[j].val);
        }
        if(l2 < l3) {
            revchange(j - l2, j - l3, -b[j].val);
        }
        if(l3 < n) {
            revchange(j - l3, j - n, b[j].val);
        }
    }
    long long ans_val = INF;
    int ans_k;
    for(long long cur = 0, k = 0; k < n; k++) {
        cur += sum[k];
        if(cur < ans_val) {
            ans_val = cur;
            ans_k = k;
        }
    }
    for(int i = 0; i < n; i++) {
        ans[a[i].idx] = b[(i + ans_k) % n].idx;
    }
    printf("%lld\n", ans_val);
    for(int i = 1; i <= n; i++) {
        printf("%d ", ans[i]);
    }
    printf("\n");
    return 0;
}
