#include <cstdio>

const int MAXN = 2e5 + 5;

int n, q, x;
int a[MAXN];

struct SGT {
    struct {
        int val;
        bool mark;
    } tree[MAXN * 4];

    void build(int root, int left, int right) {
        tree[root].mark = false;
        if(left == right) {
            if(a[left] <= x) tree[root].val = 0;
            else tree[root].val = 1;
        }
        else {
            int mid = (left + right) / 2;
            build(root << 1, left, mid);
            build(root << 1 | 1, mid + 1, right);
            tree[root].val = tree[root << 1].val + tree[root << 1 | 1].val;
        }
    }
    void push_down(int root, int left, int right) {
        int cnt = right - left + 1;
        int val = tree[root].val / cnt;
        tree[root].mark = false;
        tree[root << 1].mark = true;
        tree[root << 1].val = val * ((cnt + 1) / 2);
        tree[root << 1 | 1].mark = true;
        tree[root << 1 | 1].val = val * (cnt / 2);
    }
    void modify(int root, int left, int right, int l, int r, int val) {
        if(l > r) return;
        if(right < l || r < left) return;
        if(l <= left && right <= r) {
            tree[root].mark = true;
            tree[root].val = val * (right - left + 1);
        }
        else {
            int mid = (left + right) / 2;
            if(tree[root].mark) push_down(root, left, right);
            modify(root << 1, left, mid, l, r, val);
            modify(root << 1 | 1, mid + 1, right, l, r, val);
            tree[root].val = tree[root << 1].val + tree[root << 1 | 1].val;
        }
    }
    int query(int root, int left, int right, int l, int r) {
        if(l > r) return 0;
        if(right < l || r < left) return 0;
        if(l <= left && right <= r) {
            return tree[root].val;
        }
        else {
            int mid = (left + right) / 2;
            if(tree[root].mark) push_down(root, left, right);
            return query(root << 1, left, mid, l, r) + query(root << 1 | 1, mid + 1, right, l, r);
        }
    }
} sgt;
long long b[2][MAXN];
int cnt[2];
int main() {
    scanf("%d%d%d", &n, &q, &x);
    for(int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        if(a[i] <= x) b[0][cnt[0]++] = a[i];
        else b[1][cnt[1]++] = a[i];
    }
    for(int i = cnt[0] - 2; i >= 0; i--) b[0][i] += b[0][i + 1];
    for(int i = cnt[1] - 2; i >= 0; i--) b[1][i] += b[1][i + 1];
    sgt.build(1, 1, n);
    while(q--) {
        int p, l, r;
        scanf("%d%d%d", &p, &l, &r);
        if(p == 1) {
            int pre = sgt.query(1, 1, n, 1, l - 1);
            int cur = sgt.query(1, 1, n, l, r);
            long long ans = b[1][pre] - b[1][pre + cur];
            pre = l - 1 - pre;
            cur = r - l + 1 - cur;
            ans += b[0][pre] - b[0][pre + cur];
            printf("%lld\n", ans);
        }
        else if(p == 2) {
            int cur = sgt.query(1, 1, n, l, r);
            sgt.modify(1, 1, n, l, r - cur, 0);
            sgt.modify(1, 1, n, r - cur + 1, r, 1);
        }
        else if(p == 3) {
            int cur = sgt.query(1, 1, n, l, r);
            sgt.modify(1, 1, n, l, l + cur - 1, 1);
            sgt.modify(1, 1, n, l + cur, r, 0);
        }
    }
    return 0;
}