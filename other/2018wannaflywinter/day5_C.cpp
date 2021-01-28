#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN = 1e5 + 5;
typedef long long ll;

struct PSGT {
    struct {
        int num, lc, rc;
        ll sum;
    } tree[MAXN * 30];
    int cnt;

    void init() {
        cnt = 0;
    }

    int new_node() {
        tree[++cnt] = {0, 0, 0, 0};
        return cnt;
    }

    int add(int root, int left, int right, int p, int val) {
        int res = new_node();
        if(root != 0) tree[res] = tree[root];
        tree[res].num++;
        tree[res].sum += val;
        if(left < right) {
            int mid = (left + right) / 2;
            if(p <= mid) {
                tree[res].lc = add(tree[res].lc, left, mid, p, val);
            }
            else {
                tree[res].rc = add(tree[res].rc, mid + 1, right, p, val);
            }
        }
        return res;
    }
} psgt;

struct Query {
    int l, r, k;
    ll ans;
} query[MAXN * 5];
int n, q;
int a[MAXN];
ll aa[MAXN];
int buf[MAXN];
int root[MAXN];
int main() {
    scanf("%d%d", &n, &q);
    for(int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        aa[i] = aa[i - 1] + a[i];
    }
    for(int i = 0; i < q; i++) {
        scanf("%d%d%d", &query[i].l, &query[i].r, &query[i].k);
    }

    for(int exp = 30; exp >= 0; exp--) {
        int cnt_buf = 0;
        for(int i = 1; i <= n; i++) {
            if(a[i] >= (1 << exp)) {
                buf[cnt_buf++] = (a[i] + 1) / 2;
            }
        }
        sort(buf, buf + cnt_buf);
        cnt_buf = unique(buf, buf + cnt_buf) - buf;
        psgt.init();
        for(int i = 1; i <= n; i++) {
            if(a[i] >= (1 << exp)) {
                int idx = lower_bound(buf, buf + cnt_buf, (a[i] + 1) / 2) - buf;
                root[i] = psgt.add(root[i - 1], 0, cnt_buf - 1, cnt_buf - 1 - idx, (a[i] + 1) / 2);
                a[i] /= 2;
            }
            else {
                root[i] = root[i - 1];
            }
        }
        for(int i = 0; i < q; i++) {
            int rtl = root[query[i].l - 1], rtr = root[query[i].r];
            int curnum = psgt.tree[rtr].num - psgt.tree[rtl].num;
            ll cursum = psgt.tree[rtr].sum - psgt.tree[rtl].sum;
            if(query[i].k >= curnum) {
                query[i].k -= curnum;
                query[i].ans += cursum;
            }
            else {
                int left = 0, right = cnt_buf - 1;
                while(query[i].k > 0) {
                    if(left == right) {
                        query[i].ans += (long long)query[i].k * buf[cnt_buf - 1 - left];
                        query[i].k = 0;
                    }
                    else {
                        int mid = (left + right) / 2;
                        int lcl = psgt.tree[rtl].lc, lcr = psgt.tree[rtr].lc;
                        int lnum = psgt.tree[lcr].num - psgt.tree[lcl].num;
                        if(query[i].k >= lnum) {
                            query[i].k -= lnum;
                            query[i].ans += psgt.tree[lcr].sum - psgt.tree[lcl].sum;
                            rtl = psgt.tree[rtl].rc;
                            rtr = psgt.tree[rtr].rc;
                            left = mid + 1;
                        }
                        else {
                            rtl = psgt.tree[rtl].lc;
                            rtr = psgt.tree[rtr].lc;
                            right = mid;
                        }
                    }
                }
            }
        }
    }
    for(int i = 0; i < q; i++) printf("%lld\n", aa[query[i].r] - aa[query[i].l - 1] - query[i].ans);
    return 0;
}
