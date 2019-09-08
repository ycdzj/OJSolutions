#include <cstdio>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

const int MAXN = 2e5 + 5;

struct Edge {
    int v;
    int size;
};

vector<Edge> adj[MAXN];
int height[MAXN];
int clr[MAXN];
bool vis[MAXN];
int n, k;

void dfs_size(int u, int par, int par_max) {
    vector<int> prefix(adj[u].size());
    for(int pre = INT_MIN, i = 0; i < adj[u].size(); i++) {
        if(adj[u][i].v == par) {
            prefix[i] = pre;
        }
        else {
            prefix[i] = max(pre, height[adj[u][i].v]);
        }
        pre = prefix[i];
    }
    for(int suf = INT_MIN, i = adj[u].size() - 1; i >= 0; i--) {
        int cur = max(suf, par_max);
        if(i > 0) {
            cur = max(cur, prefix[i - 1]);
        }
        if(adj[u][i].v == par) {
            adj[u][i].size = par_max;
        }
        else {
            adj[u][i].size = height[adj[u][i].v];
            dfs_size(adj[u][i].v, u, cur + 1);
            suf = max(suf, height[adj[u][i].v]);
        }
    }
}

void dfs_height(int u, int par) {
    int h = 0;
    for(Edge e : adj[u]) {
        if(e.v != par) {
            dfs_height(e.v, u);
            h = max(h, height[e.v]);
        }
    }
    height[u] = 1 + h;
}
void dfs_vis(int u, int par) {
    vis[u] = true;
    for(Edge e : adj[u]) {
        if(e.v != par && !vis[e.v]) {
            dfs_vis(e.v, u);
        }
    }
}
void update(vector<pair<int, int>> &v, pair<int, int> val) {
    v.push_back(val);
    for(int i = v.size() - 1; i >= 1; i--) {
        if(v[i - 1] < v[i]) {
            swap(v[i - 1], v[i]);
        }
        else {
            break;
        }
    }
    if(v.size() > 3) {
        v.pop_back();
    }
}
void dfs_clr(int u, int par, int par_clr, bool dec) {
    if(dec) {
        par_clr += k - 1;
    }
    else {
        par_clr++;
    }
    par_clr %= k;
    clr[u] = par_clr;
    for(Edge e : adj[u]) {
        if(e.v != par) {
            dfs_clr(e.v, u, par_clr, dec);
        }
    }
}
int main() {
    scanf("%d%d", &n, &k);
    for(int i = 1; i < n; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        adj[u].push_back({v, -1});
        adj[v].push_back({u, -1});
    }
    if(k == 2) {
        dfs_clr(1, 1, 0, true);
        printf("Yes\n");
        for(int i = 1; i <= n; i++) {
            printf("%d ", clr[i] + 1);
        }
        printf("\n");
    }
    else {
        dfs_height(1, 1);
        dfs_size(1, 1, 0);
        vector<pair<int, int>> seq;
        bool flag = true;
        for(int i = 1; i <= n; i++) {
            vector<pair<int, int>> cur;
            for(int j = 0; j < adj[i].size(); j++) {
                update(cur, {adj[i][j].size, adj[i][j].v});
            }
            int cnt[3] = {0, 0, 0};
            int tot = 0, bag;
            for(int x = 0; x < cur.size(); x++) {
                for(int y = x + 1; y < cur.size(); y++) {
                    if(cur[x].first + cur[y].first >= k - 1) {
                        if(cnt[x]++ == 1) {
                            tot++;
                            bag = cur[x].second;
                        }
                        if(cnt[y]++ == 1) {
                            tot++;
                            bag = cur[y].second;
                        }
                    }
                }
            }
            if(tot > 1) {
                flag = false;
                break;
            }
            else if(tot == 1) {
                seq.push_back({i, bag});
            }
        }
        if(flag) {
            int root = 0, root_par;
            for(auto pr : seq) {
                if(!vis[pr.first]) {
                    root = pr.first;
                    root_par = pr.second;
                    dfs_vis(pr.first, pr.second);
                }
            }
            if(root == 0) {
                for(int i = 1; i <= n; i++) {
                    if(adj[i].size() == 1 && adj[i][0].size >= k - 1) {
                        root = i;
                        root_par = adj[i][0].v;
                        break;
                    }
                }
            }
            if(root == 0) {
                root = 1;
                root_par = 1;
            }
            for(int i = 0; i < adj[root].size(); i++) {
                dfs_clr(adj[root][i].v, root, 0, adj[root][i].v == root_par);
            }
            printf("Yes\n");
            for(int i = 1; i <= n; i++) {
                printf("%d ", clr[i] + 1);
            }
            printf("\n");
        }
        else {
            printf("No\n");
        }
    }
    return 0;
}
