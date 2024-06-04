#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int INF = 1e9;

int bfs(vector<vector<int>> &adj, int n, int s, int t, int dis_u, int dis_v) {
    vector<int> dis(n, INF);
    queue<int> que;
    dis[s] = 0;
    que.push(s);
    while(!que.empty()) {
        int u = que.front();
        que.pop();
        for(auto v : adj[u]) {
            if((u == dis_u && v == dis_v) || (v == dis_u && u == dis_v)) {
                continue;
            }
            if(dis[v] == INF) {
                dis[v] = dis[u] + 1;
                que.push(v);
            }
        }
    }
    return dis[t];
}

int main() {
    int n;
    cin >> n;
    vector<long long> a(n);
    vector<int> idx[65];
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        for(int j = 0; j < 60; j++) {
            if(a[i] >> j & 1) {
                idx[j].push_back(i);
            }
        }
    }
    for(int i = 0; i < 60; i++) {
        if(idx[i].size() >= 3) {
            cout << 3 << endl;
            return 0;
        }
    }
    vector<vector<int>> adj(n);
    for(int i = 0; i < 60; i++) {
        if(idx[i].size() == 2) {
            int u = idx[i][0];
            int v = idx[i][1];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
    }
    int ans = INF;
    for(int i = 0; i < 60; i++) {
        if(idx[i].size() == 2) {
            ans = min(ans, 1 + bfs(adj, n, idx[i][0], idx[i][1], idx[i][0], idx[i][1]));
        }
    }
    if(ans == INF) {
        ans = -1;
    }
    cout << ans << endl;
    return 0;
}
