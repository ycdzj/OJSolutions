#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

const int MAXN = 1005;
vector<int> adj[MAXN * 2];
int n, m;

int f[MAXN * 2], indeg[MAXN * 2];
int ans[MAXN * 2];

int find(int x) {
    if(f[x] != x) f[x] = find(f[x]);
    return f[x];
}
void merge(int x, int y) {
    x = find(x);
    y = find(y);
    if(x != y) {
        f[x] = y;
        indeg[y] += indeg[x];
    }
}

char str[MAXN];
int main() {
    scanf("%d%d", &n, &m);
    for(int i = 0; i < n + m; i++) f[i] = i;
    for(int i = 0; i < n; i++) {
        scanf("%s", str);
        for(int j = 0; j < m; j++) {
            int x = find(i), y = find(n + j);
            if(str[j] == '=') {
                merge(x, y);
            }
            else if(str[j] == '<') {
                adj[x].push_back(y);
                indeg[y]++;
            }
            else if(str[j] == '>') {
                adj[y].push_back(x);
                indeg[x]++;
            }
        }
    }

    queue<int> que;
    for(int i = 0; i < n + m; i++) {
        int fi = find(i);
        if(f[i] == i) {
            if(indeg[i] == 0) {
                ans[i] = 1;
                que.push(i);
            }
        }
        else {
            for(auto v : adj[i]) {
                adj[fi].push_back(v);
            }
        }
    }
    while(!que.empty()) {
        int u = que.front(); que.pop();
        for(auto v : adj[u]) {
            v = find(v);
            ans[v] = max(ans[v], ans[u] + 1);
            if(--indeg[v] == 0) {
                que.push(v);
            }
        }
    }
    for(int i = 0; i < n + m; i++) {
        if(f[i] == i && indeg[i] != 0) {
            printf("No\n");
            return 0;
        }
    }
    printf("Yes\n");
    for(int i = 0; i < n; i++) {
        printf("%d ", ans[find(i)]);
    }
    printf("\n");
    for(int i = n; i < n + m; i++) {
        printf("%d ", ans[find(i)]);
    }
    printf("\n");
    return 0;
}
