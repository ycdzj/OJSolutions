#include <cstdio>
#include <vector>
using namespace std;

const int MAXN = 1e5 + 5;

int n;
int l[MAXN], r[MAXN];
bool vis[MAXN];

int cnt;
int val[MAXN];
int min_idx[MAXN];
int cnt_node[MAXN];
const int INF = 1e9;
void dfs(int u) {
    int lval = INF;
    int rval = INF;

    if(l[u] != 0) {
        lval = min_idx[l[u]];
    }
    if(r[u] != 0) {
        rval = min_idx[r[u]];
    }
    if(u < lval && u < rval) {
        if(l[u] == 0 || r[u] == 0) {
            val[u] = cnt++;
            if(l[u] != 0) {
                dfs(l[u]);
            }
            if(r[u] != 0) {
                dfs(r[u]);
            }
        }
        else {
            if(cnt_node[l[u]] < cnt_node[r[u]]) {
                dfs(l[u]);
                val[u] = cnt++;
                dfs(r[u]);
            }
            else if(cnt_node[r[u]] < cnt_node[l[u]]) {
                dfs(r[u]);
                val[u] = cnt++;
                dfs(l[u]);
            }
            else {
                if(min_idx[l[u]] < min_idx[r[u]]) {
                    dfs(l[u]);
                    val[u] = cnt++;
                    dfs(r[u]);
                }
                else {
                    dfs(r[u]);
                    val[u] = cnt++;
                    dfs(l[u]);
                }
            }
        }
    }
    else {
        if(l[u] == 0 || r[u] == 0) {
            if(l[u] != 0) {
                dfs(l[u]);
            }
            if(r[u] != 0) {
                dfs(r[u]);
            }
            val[u] = cnt++;
        }
        else {
            if(min_idx[l[u]] < min_idx[r[u]]) {
                dfs(l[u]);
                val[u] = cnt++;
                dfs(r[u]);
            }
            else {
                dfs(r[u]);
                val[u] = cnt++;
                dfs(l[u]);
            }
        }
    }
}

void predfs(int u) {
    min_idx[u] = u;
    cnt_node[u] = 1;
    if(l[u] != 0) {
        predfs(l[u]);
        min_idx[u] = min(min_idx[u], min_idx[l[u]]);
        cnt_node[u] += cnt_node[l[u]];
    }
    if(r[u] != 0) {
        predfs(r[u]);
        min_idx[u] = min(min_idx[u], min_idx[r[u]]);
        cnt_node[u] += cnt_node[r[u]];
    }
}

const int MOD = 1e9 + 7;
inline int addmod(int a, int b) { return (a + b) % MOD; }
inline int mulmod(long long a, int b) { return (a * b) % MOD; }
void print(bool rev) {
    int ans = 0;
    for(int i = 1, po = 233; i <= n; i++) {
        int cur = val[i];
        if(rev) {
            cur = n + 1 - cur;
        }
        cur = (cur ^ i);
        ans = addmod(ans, mulmod(cur, po));
        po = mulmod(po, 233);
    }
    printf("%d\n", ans);
}

int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        for(int i = 1; i <= n; i++) {
            vis[i] = false;
        }
        for(int i = 1; i <= n; i++) {
            scanf("%d%d", &l[i], &r[i]);
            vis[l[i]] = true;
            vis[r[i]] = true;
        }
        int root;
        for(int i = 1; i <= n; i++) {
            if(!vis[i]) {
                root = i;
                break;
            }
        }

        cnt = 1;
        predfs(root);
        dfs(root);

        print(false);
    }
    return 0;
}
