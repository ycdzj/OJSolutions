#include <cstdio>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

const int MAXN = 1e6 + 5;

int n, m;
vector<int> adj[MAXN];
int dfn[MAXN], low[MAXN], clk;
int sccno[MAXN], cnt_scc;

stack<int> stk;
void scc_dfs(int u) {
    dfn[u] = low[u] = ++clk;
    stk.push(u);

    for(auto v : adj[u]) {
        if(dfn[v] == 0) {
            scc_dfs(v);
            low[u] = min(low[u], low[v]);
        }
        else if(sccno[v] == 0) {
            low[u] = min(low[u], dfn[v]);
        }
    }

    if(low[u] == dfn[u]) {
        cnt_scc++;
        int x;
        do {
            x = stk.top();
            stk.pop();
            sccno[x] = cnt_scc;
        } while(x != u);
    }
}

void find_scc() {
    for(int i = 1; i <= n; i++) {
        sccno[i] = 0;
        dfn[i] = 0;
    }
    cnt_scc = 0;
    clk = 0;
    for(int i = 1; i <= n; i++) {
        if(dfn[i] == 0) {
            scc_dfs(i);
        }
    }
}

bool vis[MAXN];

void init() {
    for(int i = 1; i <= n; i++) {
        adj[i].clear();
        vis[i] = false;
    }
}


int main() {
    int t;
    scanf("%d", &t);
    while(t--) {
        scanf("%d%d", &n, &m);
        init();
        for(int i = 0; i < m; i++) {
            int u, v;
            scanf("%d%d", &u, &v);
            adj[u].push_back(v);
        }
        find_scc();
        if(cnt_scc == 1) {
            printf("No\n");
        }
        else {
            for(int i = 1; i <= n; i++) {
                for(auto j : adj[i]) {
                    if(sccno[i] != sccno[j]) {
                        vis[sccno[j]] = true;
                    }
                }
            }
            int cnt_cat = 0;
            for(int i = 1; i <= n; i++) {
                if(!vis[sccno[i]]) {
                    cnt_cat++;
                }
            }
            if(cnt_cat == n) {
                for(int i = 1; i <= n; i++) {
                    if(sccno[i] == 1) {
                        cnt_cat--;
                    }
                }
                vis[1] = true;
            }
            printf("Yes\n");
            printf("%d %d\n", n - cnt_cat, cnt_cat);
            for(int i = 1; i <= n; i++) {
                if(vis[sccno[i]]) {
                    printf("%d ", i);
                }
            }
            printf("\n");
            for(int i = 1; i <= n; i++) {
                if(!vis[sccno[i]]) {
                    printf("%d ", i);
                }
            }
            printf("\n");
        }
    }
    return 0;
}
