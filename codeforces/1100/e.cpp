#include <cstdio>
#include <queue>
#include <vector>
using namespace std;
const int MAXN = 1e5 + 5;
struct Edge {
    int v, w, id;
};
vector<Edge> adj[MAXN];
int n, m;
int indeg[MAXN];
int idx[MAXN];
bool check(int x) {
    for(int i = 1; i <= n; i++) indeg[i] = 0;
    for(int i = 1; i <= n; i++) {
        for(auto e : adj[i]) if(e.w > x) {
            indeg[e.v]++;
        }
    }
    queue<int> que;
    for(int i = 1; i <= n; i++) if(indeg[i] == 0) que.push(i);
    int cur = 0;
    while(!que.empty()) {
        int u = que.front(); que.pop();
        idx[u] = cur++;
        for(auto e : adj[u]) if(e.w > x) {
            if(--indeg[e.v] == 0) {
                que.push(e.v);
            }
        }
    }
    return cur == n;
}
int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= m; i++) {
        int u, v, w; scanf("%d%d%d", &u, &v, &w);
        adj[u].push_back({v, w, i});
    }
    int l = 0, r = 1e9;
    while(l < r) {
        int mid = l + (r - l) / 2;
        if(check(mid)) r = mid;
        else l = mid + 1;
    }
    check(l);
    vector<int> ans;
    for(int i = 1; i <= n; i++) {
        for(auto e : adj[i]) {
            if(idx[i] > idx[e.v]) ans.push_back(e.id);
        }
    }
    printf("%d %d\n", l, (int)ans.size());
    for(auto val : ans) printf("%d ", val);
    printf("\n");
    return 0;
}