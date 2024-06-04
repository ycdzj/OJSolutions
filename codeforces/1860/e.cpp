#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

const int INF = 1e9;
const int A = 26 * 26;

struct Edge {
  int v, w;
};

void bfs(int s, const vector<vector<Edge>>& adj, vector<int>& dis) {
  dis.assign(adj.size(), INF);
  static deque<int> que;

  dis[s] = 0;
  que.push_back(s);
  while (!que.empty()) {
    int u = que.front();
    que.pop_front();
    for (auto [v, w] : adj[u]) {
      if (dis[v] > dis[u] + w) {
        dis[v] = dis[u] + w;
        if (w == 0) {
          que.push_front(v);
        } else {
          que.push_back(v);
        }
      }
    }
  }
}

class Solver {
  int n;
  string s;
  int m;
  vector<pair<int, int>> queries;

 public:
  void read() {
    cin >> s >> m;
    queries.resize(m);
    for (int i = 0; i < m; i++) {
      cin >> queries[i].first >> queries[i].second;
    }
    n = s.length();
  }

  void solve() {
    int cnt_nodes = n - 1 + A;
    vector<vector<Edge>> adj(cnt_nodes);
    for (int i = 0; i + 1 < n; i++) {
      if (i >= 1) {
        adj[i].push_back({i - 1, 1});
      }
      if (i + 1 < n - 1) {
        adj[i].push_back({i + 1, 1});
      }
      int v = n - 1 + (s[i] - 'a') * 26 + s[i + 1] - 'a';
      adj[i].push_back({v, 1});
      adj[v].push_back({i, 0});
    }

    vector<int> dis[A];
    for (int i = 0; i < A; i++) {
      bfs(n - 1 + i, adj, dis[i]);
    }

    vector<vector<Edge>> rev_adj(cnt_nodes);
    for (int u = 0; u < cnt_nodes; u++) {
      for (auto [v, w] : adj[u]) {
        rev_adj[v].push_back({u, w});
      }
    }

    vector<int> rev_dis[A];
    for (int i = 0; i < A; i++) {
      bfs(n - 1 + i, rev_adj, rev_dis[i]);
    }

    for (auto [u, v] : queries) {
      int ans = abs(u - v);
      for (int i = 0; i < A; i++) {
        ans = min(ans, rev_dis[i][u - 1] + dis[i][v - 1]);
      }
      cout << ans << endl;
    }
  }
};

int main() {
  ios::sync_with_stdio(false);
  int t = 1;
  // cin >> t;
  while (t--) {
    Solver solver;
    solver.read();
    solver.solve();
  }
  return 0;
}
