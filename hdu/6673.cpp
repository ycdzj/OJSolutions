#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

struct ZkwNode {
    int val, idx;
    bool operator < (const ZkwNode &node) const {
        return val < node.val;
    }
};
struct Zkw {
    vector<ZkwNode> tree;
    int n;
    Zkw(int n_)
    : n(n_) {
        tree.resize(2 * n);
    }

public:
    void change(int p, int val) {
        p += n;
        tree[p].idx = p - n;
        tree[p].val += val;
        for(p >>= 1; p >= 1; p >>= 1) {
            tree[p] = max(tree[p << 1], tree[p << 1 | 1]);
        }
    }

    ZkwNode query(int l, int r) {
        l += n;
        r += n;
        ZkwNode res = tree[r];
        for(; l < r; l >>= 1, r >>= 1) {
            if(l & 1) res = max(res, tree[l++]);
            if(r & 1) res = max(res, tree[--r]);
        }
        return res;
    }
};



int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        int l, p, n, m, d;
        scanf("%d%d%d%d%d", &l, &p, &n, &m, &d);
        Zkw zkw(l + 1);
        for(int i = 1; i <= l; i++) {
            int c;
            scanf("%d", &c);
            zkw.change(i, c);
        }
        vector<int> events(100005, -2), y(m);
        for(int i = 0; i < n; i++) {
            int t;
            scanf("%d", &t);
            events[t] = -1;
        }
        for(int i = 0; i < m; i++) {
            int t;
            scanf("%d", &t);
            events[t] = i;
        }
        for(int i = 0; i < m; i++) {
            scanf("%d", &y[i]);
            zkw.change(y[i], -1);
        }
        int ans = 0;
        for(int i = events.size() - 1; i >= 0; i--) {
            if(events[i] >= 0) {
                zkw.change(y[events[i]], 1);
            }
            else if(events[i] == -1) {
                if(i <= d) {
                    int left = max(p - (d - i), 1);
                    int right = min(p + (d - i), l);
                    ZkwNode res = zkw.query(left, right);
                    if(res.val > 0) {
                        zkw.change(res.idx, -1);
                        ans++;
                    }
                }
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
