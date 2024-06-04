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

const long long INF = 1e18;

struct QueueItem {
  int u, pre;
  long long cnt;
  int balance;
  bool operator<(const QueueItem& other) const {
    if (cnt != other.cnt) {
      return cnt > other.cnt;
    }
    return balance < other.balance;
  }
};

class Solver {
  int n, m, p;
  vector<vector<pair<int, int>>> adj;
  vector<int> w;

 public:
  void read() {
    cin >> n >> m >> p;
    adj.resize(n + 1);
    w.resize(n + 1);
    for (int i = 1; i <= n; i++) {
      cin >> w[i];
    }
    for (int i = 0; i < m; i++) {
      int a, b, s;
      cin >> a >> b >> s;
      adj[a].emplace_back(b, s);
    }
  }

  void solve() {
    vector<vector<pair<long long, int>>> dis(
        n + 1, vector<pair<long long, int>>(n + 1, {INF, 0}));
    priority_queue<QueueItem> que;
    dis[1][1] = {0, p};
    que.push({1, 1, 0, p});
    while (!que.empty()) {
      QueueItem item = que.top();
      que.pop();

      int u = item.u;
      int pre = item.pre;
      long long cnt = item.cnt;
      int balance = item.balance;
      if (w[u] > w[pre]) {
        pre = u;
      }
      for (auto [v, s] : adj[u]) {
        long long need_cnt = (max(s - balance, 0) + w[pre] - 1) / w[pre];
        long long next_cnt = cnt + need_cnt;
        int next_balance = balance - s + need_cnt * w[pre];
        if (dis[v][pre].first > next_cnt ||
            (dis[v][pre].first == next_cnt &&
             dis[v][pre].second < next_balance)) {
          dis[v][pre] = {next_cnt, next_balance};
          que.push({v, pre, next_cnt, next_balance});
        }
      }
    }

    long long ans = INF;
    for (int i = 1; i <= n; i++) {
      ans = min(ans, dis[n][i].first);
    }
    if (ans == INF) {
      ans = -1;
    }
    cout << ans << endl;
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
