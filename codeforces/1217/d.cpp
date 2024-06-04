#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 5005;

vector<int> adj[MAXN];
vector<pair<int, int>> edges;
int n, m;
int clr[MAXN];
bool flag;

void dfs(int u) {
    clr[u] = 1;
    for(int v : adj[u]) {
        if(clr[v] == 0) {
            dfs(v);
        }
        else if(clr[v] == 1) {
            flag = true;
        }
    }
    clr[u] = 2;
}

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        edges.emplace_back(u, v);
        adj[u].push_back(v);
    }
    for(int i = 1; i <= n; i++) {
        if(clr[i] == 0) {
            dfs(i);
        }
    }
    if(!flag) {
        printf("1\n");
        for(int i = 0; i < m; i++) {
            printf("1 ");
        }
        printf("\n");
    }
    else {
        printf("2\n");
        for(auto pr : edges) {
            if(pr.first > pr.second) {
                printf("1 ");
            }
            else {
                printf("2 ");
            }
        }
        printf("\n");
    }
    return 0;
}
