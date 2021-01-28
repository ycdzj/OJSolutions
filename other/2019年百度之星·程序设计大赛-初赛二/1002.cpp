#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

struct Graph {
    bool vis[105];
    int link[105];
    vector<int> adj[105];
    int n;
    void init(int n_) {
        n = n_;
        for(int i = 0; i < n; i++) {
            adj[i].clear();
        }
    }
    bool hungarian_dfs(int u) {
        for(int i = 0; i < adj[u].size(); i++) {
            int v = adj[u][i];
            if(!vis[v]) {
                vis[v] = true;
                if(link[v] == -1 || hungarian_dfs(v)) {
                    link[v] = u;
                    link[u] = v;
                    return true;
                }
            }
        }
        return false;
    }
    int hungarian() {
        memset(link, 0xff, sizeof(link));
        int res = 0;
        for(int i = 0; i < n; i++) {
            if(link[i] == -1) {
                memset(vis, 0, sizeof(vis));
                if(hungarian_dfs(i)) res++;
            }
        }
        return res;
    }
} G;

int n, m;
bool vis[55][55];
char str1[55], str2[55];

int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &n, &m);
        memset(vis, 0, sizeof(vis));
        for(int i = 0; i < n; i++) {
            scanf("%s%s", str1, str2);
            for(int j = 0; j < m; j++) {
                for(int k = 0; k < m; k++) {
                    if(str2[k] != str1[j]) {
                        vis[j][k] = true;
                    }
                }
            }
        }
        G.init(2 * m);
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < m; j++) {
                if(!vis[i][j]) {
                    G.adj[i].push_back(m + j);
                }
            }
        }
        if(G.hungarian() == m) {
            for(int i = 0; i < m; i++) {
                printf("%d", G.link[i] - m + 1);
                if(i + 1 < m) printf(" ");
                else printf("\n");
            }
        }
        else {
            printf("-1\n");
        }
    }
    return 0;
}