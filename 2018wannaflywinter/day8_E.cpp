#include <cstdio>

const int MOD = 998244353;
typedef long long ll;

const int MAXN = 1e5 + 5;
struct Node {
    int idx;
    bool mark;
} tree[MAXN * 2 * 4];
int mat[MAXN * 50][3][3], cnt;
int n, m;

void mulmat(int res[3][3], int a[3][3], int b[3][3]) {
    static int tmp[3][3];
    for(int i = 0; i < 3; i++) for(int j = 0; j < 3; j++) {
        ll sum = 0;
        for(int k = 0; k < 3; k++) sum += (ll)a[i][k] * b[k][j];
        tmp[i][j] = sum % MOD;
    }
    for(int i = 0; i < 3; i++) for(int j = 0; j < 3; j++) {
        res[i][j] = tmp[i][j];
    }
}

void build(int root, int left, int right) {
    tree[root].mark = false;
    if(left == right) {
        if(left <= n) {
            tree[root].idx = left;
        }
        else {
            tree[root].idx = n + 1;
        }
    }
    else {
        int mid = (left + right) / 2;
        build(root << 1, left, mid);
        build(root << 1 | 1, mid + 1, right);
        mulmat(mat[cnt], mat[tree[root << 1].idx], mat[tree[root << 1 | 1].idx]);
        tree[root].idx = cnt++;
    }
}
void push_down(int root) {
    if(tree[root].mark) {
        tree[root << 1].idx = tree[root].idx - 1;
        tree[root << 1 | 1].idx = tree[root].idx - 1;
        tree[root << 1].mark = true;
        tree[root << 1 | 1].mark = true;
        tree[root].mark = false;
    }
}
void modify(int root, int left, int right, int l, int r, int idx) {
    if(right < l || r < left) return;
    if(l <= left && right <= r) {
        tree[root].mark = true;
        tree[root].idx = idx;
    }
    else {
        push_down(root);
        int mid = (left + right) / 2;
        modify(root << 1, left, mid, l, r, idx - 1);
        modify(root << 1 | 1, mid + 1, right, l, r, idx - 1);
        mulmat(mat[cnt], mat[tree[root << 1].idx], mat[tree[root << 1 | 1].idx]);
        tree[root].idx = cnt++;
    }
}
int resmat[3][3];
void query(int root, int left, int right, int l, int r) {
    if(right < l || r < left) return;
    if(l <= left && right <= r) {
        mulmat(resmat, resmat, mat[tree[root].idx]);
    }
    else {
        push_down(root);
        int mid = (left + right) / 2;
        query(root << 1, left, mid, l, r);
        query(root << 1 | 1, mid + 1, right, l, r);
    }
}
int main() {
    scanf("%d%d", &n, &m);
    n--;
    for(int i = 1; i <= n; i++) {
        for(int x = 0; x < 3; x++) for(int y = 0; y < 3; y++) {
            scanf("%d", &mat[i][x][y]);
        }
    }
    cnt = n + 2;
    int exp = 0;
    while((1 << exp) < n) exp++;
    build(1, 1, 1 << exp);
    while(m-- > 0) {
        int op, l, r;
        scanf("%d%d%d", &op, &l, &r);
        if(op == 1) {
            for(int i = 0; i < 3; i++) for(int j = 0; j < 3; j++) {
                scanf("%d", &mat[cnt][i][j]);
            }
            cnt++;
            for(int i = 1; i <= exp; i++) {
                mulmat(mat[cnt], mat[cnt - 1], mat[cnt - 1]);
                cnt++;
            }
            modify(1, 1, 1 << exp, l, r, cnt - 1);
        }
        else if(op == 2) {
            for(int i = 0; i < 3; i++) for(int j = 0; j < 3; j++) {
                if(i == j) resmat[i][j] = 1;
                else resmat[i][j] = 0;
            }
            query(1, 1, 1 << exp, l, r - 1);
            ll ans = 0;
            for(int i = 0; i < 3; i++) for(int j = 0; j < 3; j++) {
                ans += resmat[i][j];
            }
            printf("%lld\n", ans % MOD);
        }
    }
    return 0;
}