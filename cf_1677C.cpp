#include <algorithm>
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

class Solver {
  int n;
  vector<vector<int>> adj;

  vector<bool> vis;
  int search(int s) {
    queue<int> que;
    vis[s] = true;
    que.push(s);
    int cnt = 0;
    while(!que.empty()) {
      int u = que.front();
      que.pop();
      cnt++;
      for (int v : adj[u]) {
        if (!vis[v]) {
          vis[v] = true;
          que.push(v);
        }
      }
    }
    return cnt;
  }
 public:
  void read() {
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
      cin >> a[i];
    }

    adj.resize(n + 1);
    for (int i = 0; i < n; i++) {
      int b;
      cin >> b;
      adj[a[i]].push_back(b);
      adj[b].push_back(a[i]);
    }
  }

  void solve() {
    vis.resize(n + 1);
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
      if (!vis[i]) {
        cnt += search(i) / 2;
      }
    }
    cout << 2ll * cnt * (n - cnt) << endl;
  }
};

int main() {
  ios::sync_with_stdio(false);
  int t = 1;
  cin >> t;
  while (t--) {
    Solver solver;
    solver.read();
    solver.solve();
  }
  return 0;
}
