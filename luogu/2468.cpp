#include <cstdio>
#include <vector>
using namespace std;
const int MAXN = 500005;
const int INF = 1e9 + 5;
struct PSGT {
    struct Node {
        int sum;
        int lc, rc;
    } tree[MAXN * 30];
    int cnt_node;
    int copy_of(int u) {
        tree[cnt_node] = tree[u];
        return cnt_node++;
    }
    void init() {
        cnt_node = 1;
    }
    int build(int l, int r) {
        int root = cnt_node++;
        if(l == r) {
            tree[root].lc = tree[root].rc = -1;
            tree[root].sum = 0;
        }
        else {
            int mid = (l + r) / 2;
            int lc = build(l, mid), rc = build(mid + 1, r);
            tree[root].lc = lc;
            tree[root].rc = rc;
            tree[root].sum = tree[lc].sum + tree[rc].sum;
        }
        return root;
    }
    int modify(int root, int left, int right, int p, int val) {
        int res = copy_of(root);
        if(left == p && right == p) tree[res].sum += val;
        else {
            int mid = (left + right) / 2;
            if(p <= mid) tree[res].lc = modify(tree[root].lc, left, mid, p, val);
            else tree[res].rc = modify(tree[root].rc, mid + 1, right, p, val);
            tree[res].sum = tree[tree[res].lc].sum + tree[tree[res].rc].sum;
        }
        return res;
    }
} psgt;
int cnt[205][205][1005], sum[205][205][1005];
int root_sum[500005], root_cnt[500005];
int r, c, m;
pair<int, int> get(int x1, int y1, int x2, int y2, int rt1, int rt2, int rt3, int rt4, int lval, int rval) {
    pair<int, int> res;
    if(r == 1) {
        res.first = psgt.tree[rt2].sum - psgt.tree[rt1].sum;
        res.second = psgt.tree[rt4].sum - psgt.tree[rt3].sum;
    }
    else {
        res.first = sum[x2][y2][rval] - sum[x1 - 1][y2][rval] - sum[x2][y1 - 1][rval] + sum[x1 - 1][y1 - 1][rval];
        res.first -= sum[x2][y2][lval - 1] - sum[x1 - 1][y2][lval - 1] - sum[x2][y1 - 1][lval - 1] + sum[x1 - 1][y1 - 1][lval - 1];
        res.second = cnt[x2][y2][rval] - cnt[x1 - 1][y2][rval] - cnt[x2][y1 - 1][rval] + cnt[x1 - 1][y1 - 1][rval];
        res.second -= cnt[x2][y2][lval - 1] - cnt[x1 - 1][y2][lval - 1] - cnt[x2][y1 - 1][lval - 1] + cnt[x1 - 1][y1 - 1][lval - 1];
    }
    return res;
}
int solve(int x1, int y1, int x2, int y2, int rt1, int rt2, int rt3, int rt4, int lval, int rval, int h) {
    if(lval == rval) {
        if(get(x1, y1, x2, y2, rt1, rt2, rt3, rt4, lval, rval).first < h) return INF;
        return (h + lval - 1) / lval;
    }
    else {
        int mid = lval + (rval - lval) / 2;
        pair<int, int> s = get(x1, y1, x2, y2, psgt.tree[rt1].rc, psgt.tree[rt2].rc, psgt.tree[rt3].rc, psgt.tree[rt4].rc, mid + 1, rval);
        if(s.first >= h) {
            if(rt1) rt1 = psgt.tree[rt1].rc;
            if(rt2) rt2 = psgt.tree[rt2].rc;
            if(rt3) rt3 = psgt.tree[rt3].rc;
            if(rt4) rt4 = psgt.tree[rt4].rc;
            return solve(x1, y1, x2, y2, rt1, rt2, rt3, rt4, mid + 1, rval, h);
        }
        else {
            if(rt1) rt1 = psgt.tree[rt1].lc;
            if(rt2) rt2 = psgt.tree[rt2].lc;
            if(rt3) rt3 = psgt.tree[rt3].lc;
            if(rt4) rt4 = psgt.tree[rt4].lc;
            return s.second + solve(x1, y1, x2, y2, rt1, rt2, rt3, rt4, lval, mid, h - s.first);
        }
    }
}
int main() {
    scanf("%d%d%d", &r, &c, &m);
    if(r != 1) {
        for(int i = 1; i <= r; i++) for(int j = 1; j <= c; j++) {
            int a; scanf("%d", &a);
            cnt[i][j][a]++;
            for(int x = 1; x <= 1000; x++) {
                cnt[i][j][x] += cnt[i - 1][j][x];
                cnt[i][j][x] += cnt[i][j - 1][x];
                cnt[i][j][x] -= cnt[i - 1][j - 1][x];
                sum[i][j][x] = cnt[i][j][x] * x;
            }
        }
        for(int i = 1; i <= r; i++) for(int j = 1; j <= c; j++) {
            for(int x = 1; x <= 1000; x++) {
                cnt[i][j][x] += cnt[i][j][x - 1];
                sum[i][j][x] += sum[i][j][x - 1];
            }
        }
    }
    else {
        psgt.init();
        root_sum[0] = psgt.build(1, 1000);
        root_cnt[0] = psgt.build(1, 1000);
        for(int i = 1; i <= c; i++) {
            int a; scanf("%d", &a);
            root_cnt[i] = psgt.modify(root_cnt[i - 1], 1, 1000, a, 1);
            root_sum[i] = psgt.modify(root_sum[i - 1], 1, 1000, a, a);
        }
    }
    while(m--) {
        int x1, y1, x2, y2, h;
        scanf("%d%d%d%d%d", &x1, &y1, &x2, &y2, &h);
        int ans = solve(x1, y1, x2, y2, root_sum[y1 - 1], root_sum[y2], root_cnt[y1 - 1], root_cnt[y2], 1, 1000, h);
        if(ans >= INF) printf("Poor QLW\n");
        else printf("%d\n", ans);
    }

    return 0;
}