#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

const int MAXN = 1005;

int n, m;
vector<int> adj[MAXN], cycle[MAXN];
int par[MAXN];
int clr[MAXN];
void dfs1(int u, int curdep) {
    clr[u] = 1;
    for(auto v : adj[u]) {
        if(clr[v] == 0) {
            par[v] = u;
            dfs1(v, curdep + 1);
        }
        else if(clr[v] == 1) {
            for(int i = u; i != v; i = par[i]) {
                cycle[v].push_back(i);
            }
        }
    }
    clr[u] = 2;
}
int x[MAXN], y[MAXN];
bool vis[MAXN];
int main() {
    scanf("%d%d", &n, &m);
    for(int i = 0; i < m; i++) {
        int u, v; scanf("%d%d", &u, &v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs1(1, 1);

    queue<int> que[2];
    int cur = 0;
    int cur_x = 1;
    vis[1] = true;
    x[1] = cur_x++;
    y[1] = 1;
    que[cur].push(1);
    while(!que[cur].empty()) {
        int nxt = cur ^ 1;
        int cur_y = 1;
        while(!que[cur].empty()) {
            int u = que[cur].front(); que[cur].pop();
            while(!cycle[u].empty()) {
                int v = cycle[u].back();
                if(!vis[v]) {
                    vis[v] = true;
                    x[v] = cur_x;
                    y[v] = cur_y++;
                    que[nxt].push(v);
                }
                cycle[u].pop_back();
            }
            for(auto v : adj[u]) {
                if(!vis[v]) {
                    vis[v] = true;
                    x[v] = cur_x;
                    y[v] = cur_y++;
                    que[nxt].push(v);
                }
            }
        }
        cur_x++;
        cur = nxt;
    }
    for(int i = 1; i <= n; i++) printf("%d %d\n", x[i], y[i]);
    return 0;
}