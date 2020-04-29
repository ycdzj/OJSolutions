#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int MAXN = 1e5 + 5;

vector<int> adj[MAXN];
int n;
int root, par[MAXN];
int cnt[MAXN];

void dfs(int cur, int pre) {
    for (int v : adj[cur]) {
        if (v == pre) {
            continue;
        }
        par[v] = cur;
        dfs(v, cur);
    }
}

bool flag;

int check(int u, int pre) {
    int pre_val = -1;
    for (int v : adj[u]) {
        if (v == pre) {
            continue;
        }
        int cur_val = check(v, u);
        if (pre_val != -1 && pre_val != cur_val) {
            flag = true;
        }
        pre_val = cur_val;
    }
    if (pre_val == -1) {
        pre_val = 0;
    }
    return pre_val ^ 1;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    if (n == 2) {
        printf("1 1\n");
        return 0;
    }
    for (int i = 1; i <= n; i++) {
        if (adj[i].size() > 1) {
            root = i;
            break;
        }
    }
    dfs(root, root);
    int ans_max = n - 1;
    for (int i = 1; i <= n; i++) {
        if (adj[i].size() == 1) {
            ans_max -= cnt[par[i]];
            cnt[par[i]] = 1;
        }
    }
    int ans_min = 1;
    check(root, root);
    if (flag) {
        ans_min = 3;
    }
    printf("%d %d\n", ans_min, ans_max);
    return 0;
}
