#include <cstdio>
#include <stack>
#include <vector>
using namespace std;

const int MAXN = 1e5 + 5;

int n;
vector<int> adj[MAXN];
int clr[MAXN];

int dfs_clr(int u) {
    int max_dep = 0;
    vector<int> deps(adj[u].size());
    for(int i = 0; i < adj[u].size(); i++) {
        deps[i] = dfs_clr(adj[u][i]);
        max_dep = max(max_dep, deps[i]);
    }
    for(int i = 0; i < adj[u].size(); i++) {
        if(deps[i] == max_dep) {
            clr[adj[u][i]] = 1;
            break;
        }
    }
    return max_dep + 1;
}

stack<int> ans;

void solve() {
    int u = 0;
    while(!adj[u].empty()) {
        int nxt = -1;
        for(int i = 0; i < adj[u].size(); i++) {
            if(clr[adj[u][i]] == 1) {
                nxt = i;
            }
            else if(clr[adj[u][i]] == 2) {
                nxt = i;
                break;
            }
        }
        swap(adj[u][nxt], adj[u][0]);
        clr[adj[u][0]] = 2;
        for(int i = 1; i < adj[u].size(); i++) {
            ans.push(adj[u][i - 1]);
            adj[adj[u][i]].push_back(adj[u][i - 1]);
            clr[adj[u][i]] = 2;
        }
        u = adj[u].back();
    }
}

void print() {
    int u = 0;
    while(true) {
        printf("%d ", u);
        if(adj[u].empty()) {
            break;
        }
        u = adj[u].back();
    }
    printf("\n");
}

int main() {
    scanf("%d", &n);
    for(int i = 1; i < n; i++) {
        int p;
        scanf("%d", &p);
        adj[p].push_back(i);
    }
    dfs_clr(0);
    solve();
    print();
    printf("%d\n", (int)ans.size());
    while(!ans.empty()) {
        printf("%d ", ans.top());
        ans.pop();
    }
    printf("\n");
    return 0;
}
