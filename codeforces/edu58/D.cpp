#include <cstdio>
#include <vector>
#include <queue>
#include <map>
using namespace std;
const int MAXN = 2e5 + 5;
int a[MAXN];
vector<int> adj[MAXN];
int n;
int pri[MAXN], dis[MAXN];
int vis[MAXN], clk;
int check(int s, int d) {
    if(a[s] % d != 0) return 0;
    clk++;
    queue<int> que;
    vis[s] = clk;
    que.push(s);
    int last;
    while(!que.empty()) {
        last = que.front(); que.pop();
        for(auto v : adj[last]) if(a[v] % d == 0 && vis[v] != clk) {
            vis[v] = clk;
            que.push(v);
        }
    }
    dis[last] = 1;
    while(a[last] % d == 0) a[last] /= d;
    que.push(last);
    int res;
    while(!que.empty()) {
        last = que.front(); que.pop();
        res = dis[last];
        for(auto v : adj[last]) if(a[v] % d == 0) {
            dis[v] = dis[last] + 1;
            while(a[v] % d == 0) a[v] /= d;
            que.push(v);
        }
    }
    return res;
}
int main() {
    for(int i = 1; i < MAXN; i++) pri[i] = i;
    for(int i = 2; i < MAXN; i++) if(pri[i] == i) {
        for(int j = 2 * i; j < MAXN; j += i) pri[j] = min(pri[j], i);
    }
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
    for(int i = 1; i < n; i++) {
        int x, y; scanf("%d%d", &x, &y);
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    int ans = 0;
    for(int i = 1; i <= n; i++) {
        while(a[i] > 1) {
            ans = max(ans, check(i, pri[a[i]]));
        }
    }
    printf("%d\n", ans);
    return 0;
}