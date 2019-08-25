#include <cstdio>

const int MOD = 998244353;
inline int addmod(int a, int b) {
    return (a + b) % MOD;
}
inline int mulmod(long long a, int b) {
    return (a * b) % MOD;
}

const int MAXM = 20;
const int MAXN = (1 << MAXM) + 5;

int tree[MAXN];
char str[MAXN];
int m, q;

int main() {
    scanf("%d%d", &m, &q);
    scanf("%s", str + 1);
    int n = 1 << (m - 1);
    for(int i = 0; i < n; i++) {
        tree[n + i] = i + 1;
    }
    for(int i = n - 1; i >= 1; i--) {
        if(str[i] == '0') {
            tree[i] = addmod(tree[i << 1], tree[i << 1 | 1]);
        }
        else {
            tree[i] = mulmod(tree[i << 1], tree[i << 1 | 1]);
        }
    }
    while(q--) {
        int t;
        scanf("%d", &t);
        if(t == 1) {
            int idx, y;
            scanf("%d%d", &idx, &y);
            --idx;
            tree[n + idx] = y;
            for(int i = (n + idx) / 2; i >= 1; i >>= 1) {
                if(str[i] == '0') {
                    tree[i] = addmod(tree[i << 1], tree[i << 1 | 1]);
                }
                else {
                    tree[i] = mulmod(tree[i << 1], tree[i << 1 | 1]);
                }
            }
        }
        else {
            int idx;
            scanf("%d", &idx);
            --idx;
            int ans = 1;
            for(int i = n + idx; i > 1; i >>= 1) {
                if(str[i >> 1] == '1') {
                    ans = mulmod(ans, tree[i ^ 1]);
                }
            }
            printf("%d\n", ans);
        }
    }
    return 0;
}
