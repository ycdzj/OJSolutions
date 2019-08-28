#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;

int n;
bool adj[105][105];
int m, p[1000006];
char str[105];

bool vis[105];

void bfs(int s, int *dis) {
    fill(vis, vis + n + 1, false);

    queue<int> que;
    dis[s] = 0;
    vis[s] = true;
    que.push(s);
    while(!que.empty()) {
        int u = que.front();
        que.pop();
        for(int v = 1; v <= n; v++) {
            if(adj[u][v] && !vis[v]) {
                vis[v] = true;
                dis[v] = dis[u] + 1;
                que.push(v);
            }
        }
    }
}

int dis[105][105];

int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) {
        scanf("%s", str);
        for(int j = 1; j <= n; j++) {
            adj[i][j] = (str[j - 1] == '1');
        }
    }
    for(int i = 1; i <= n; i++) {
        bfs(i, dis[i]);
    }
    scanf("%d", &m);
    for(int i = 0; i < m; i++) {
        scanf("%d", &p[i]);
    }
    int i = 0;
    vector<int> ans;
    while(i < m) {
        ans.push_back(p[i]);
        if(i == m - 1) {
            break;
        }
        for(int j = min(i + n - 1, m - 1); j > i; j--) {
            if(dis[p[i]][p[j]] == j - i) {
                i = j;
                break;
            }
        }
    }
    printf("%d\n", (int)ans.size());
    for(int val : ans) {
        printf("%d ", val);
    }
    printf("\n");
    return 0;
}
