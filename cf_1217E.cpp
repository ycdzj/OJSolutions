#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN = 2e5 + 5;
const int INF = 2e9;

struct ZkwItem {
    int a, b;
};

void update_item(ZkwItem &item, int x) {
    if(x < item.a) {
        item.b = item.a;
        item.a = x;
    }
    else if(x < item.b) {
        item.b = x;
    }
}

int n, m;

struct Zkw {
    ZkwItem tree[MAXN * 2];

    void update(int p, int val) {
        p += n;
        tree[p] = {val, INF};
        for(p >>= 1; p >= 1; p >>= 1) {
            tree[p] = tree[p << 1];
            update_item(tree[p], tree[p << 1 | 1].a);
            update_item(tree[p], tree[p << 1 | 1].b);
        }
    }

    ZkwItem query(int l, int r) {
        l += n;
        r += n;
        ZkwItem res = tree[r];
        for(; l < r; l >>= 1, r >>= 1) {
            if(l & 1) {
                update_item(res, tree[l].a);
                update_item(res, tree[l].b);
                l++;
            }
            if(r & 1) {
                r--;
                update_item(res, tree[r].a);
                update_item(res, tree[r].b);
            }
        }
        return res;
    }
} zkw[10];

int a[MAXN];

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        for(int val = a[i], k = 0; k < 10; val /= 10, k++) {
            if(val % 10) {
                zkw[k].update(i, a[i]);
            }
            else {
                zkw[k].update(i, INF);
            }
        }
    }
    while(m--) {
        int op;
        scanf("%d", &op);
        if(op == 1) {
            int i, x;
            scanf("%d%d", &i, &x);
            i--;
            for(int val_a = a[i], val_x = x, k = 0; k < 10; val_a /= 10, val_x /= 10, k++) {
                if(val_x % 10) {
                    zkw[k].update(i, x);
                }
                else if(val_a % 10) {
                    zkw[k].update(i, INF);
                }
            }
            a[i] = x;
        }
        else {
            int l, r;
            scanf("%d%d", &l, &r);
            l--;
            r--;
            int ans = INF;
            for(int k = 0; k < 10; k++) {
                ZkwItem cur = zkw[k].query(l, r);
                if(cur.a != INF && cur.b != INF) {
                    ans = min(ans, cur.a + cur.b);
                }
            }
            if(ans == INF) {
                ans = -1;
            }
            printf("%d\n", ans);
        }
    }
    return 0;
}
