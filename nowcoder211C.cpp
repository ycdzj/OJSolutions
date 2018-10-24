#include <cstdio>
#include <algorithm>

const int MAXN = 2e6 + 5;
struct BIT {
    int time[MAXN], n, clk;
    int tree[MAXN];
    void update(int p) {
        if(time[p] != clk) {
            time[p] = clk;
            tree[p] = 0;
        }
    }
    int lowbit(int x) { return x & (-x); }
    void modify(int p, int val) {
        while(p <= n) {
            update(p);
            tree[p] += val;
            p += lowbit(p);
        }
    }
    int query(int p) {
        int res = 0;
        while(p >= 1) {
            update(p);
            res += tree[p];
            p -= lowbit(p);
        }
        return res;
    }
} bitf, bitg;
struct Query {
    int idx, op, type;
    long long x, y;
} query[MAXN];
int ans[MAXN];
Query qbuf[MAXN];
bool cmp(Query &a, Query &b) {
    if(a.x != b.x) return a.x < b.x;
    return a.op < b.op;
}
void solve(int l, int r) {
    if(l == r) return;
    int mid = l + (r - l) / 2;
    solve(l, mid);
    solve(mid + 1, r);
    bitf.clk++;
    bitg.clk++;
    int pl = l, pr = mid + 1;
    int n_buf = 0;
    while(pl <= mid || pr <= r) {
        if(pl <= mid && (pr > r || cmp(query[pl], query[pr]))) {
            qbuf[n_buf++] = query[pl];
            if(query[pl].op == 1) {
                if(query[pl].type == 0) bitf.modify(query[pl].y, 1);
                else bitg.modify(query[pl].y, 1);
            }
            pl++;
        }
        else {
            qbuf[n_buf++] = query[pr];
            if(query[pr].op == 2) {
                int val;
                if(query[pr].type <= 1) {
                    val = bitf.query(query[pr].y);
                }
                else {
                    val = bitg.query(query[pr].y);
                }
                if(query[pr].type & 1) ans[query[pr].idx] -= val;
                else ans[query[pr].idx] += val;
            }
            pr++;
        }
    }
    for(int i = 0; i < n_buf; i++) query[l + i] = qbuf[i];
}
long long buf[MAXN];
int n;
int main() {
    scanf("%d", &n);
    int nq = 0, nb = 0, n_ans = 0;
    for(int i = 0; i < n; i++) {
        int op; scanf("%d", &op);
        if(op == 1) {
            int x, y; scanf("%d%d", &x, &y);
            query[nq++] = { -1, 1, 0, x, y };
            query[nq++] = { -1, 1, 1, x, x + y };
            buf[nb++] = x;
            buf[nb++] = y;
            buf[nb++] = x + y;
        }
        else if(op == 2) {
            int x1, y1, x2, d; scanf("%d%d%d%d", &x1, &y1, &x2, &d);
            query[nq++] = { n_ans, 2, 0, x2, y1 + d }; //D
            query[nq++] = { n_ans, 2, 1, x1 - 1, y1 + d }; //A
            query[nq++] = { n_ans, 2, 1, x2, y1 - 1 }; //E
            query[nq++] = { n_ans, 2, 0, x1 - 1, y1 - 1 }; //B
            query[nq++] = { n_ans, 2, 2, x2 + d, (long long)x2 + d + y1 }; //C
            query[nq++] = { n_ans, 2, 3, x2, (long long)x2 + y1 + d }; //D
            query[nq++] = { n_ans, 2, 1, x2 + d, y1 - 1 }; //F
            query[nq++] = { n_ans, 2, 0, x2, y1 - 1 }; //E
            n_ans++;
            buf[nb++] = x1 - 1;
            buf[nb++] = x2;
            buf[nb++] = x2 + d;
            buf[nb++] = y1 + d;
            buf[nb++] = y1 - 1;
            buf[nb++] = (long long)x2 + d + y1;
            buf[nb++] = (long long)x2 + y1 + d;
        }
    }
    std::sort(buf, buf + nb);
    nb = std::unique(buf, buf + nb) - buf;
    for(int i = 0; i < nq; i++) {
        query[i].x = std::lower_bound(buf, buf + nb, query[i].x) - buf + 1;
        query[i].y = std::lower_bound(buf, buf + nb, query[i].y) - buf + 1;
    }
    bitf.n = nb;
    bitg.n = nb;
    solve(0, nq - 1);
    for(int i = 0; i < n_ans; i++) printf("%d\n", ans[i]);
    return 0;
}