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

const int MAXM = 3;
const int MODS[MAXM] = {1000000000 + 7, 998244353, 988244353};

struct ModNumber {
  int vals[MAXM] = {0, 0, 0};

  void add(const ModNumber& other) {
    for (int j = 0; j < MAXM; j++) {
      vals[j] = (vals[j] + other.vals[j]) % MODS[j];
    }
  }

  void sub(const ModNumber& other) {
    for (int j = 0; j < MAXM; j++) {
      vals[j] = (vals[j] + MODS[j] - other.vals[j]) % MODS[j];
    }
  }

  void mul(const ModNumber& other) {
    for (int j = 0; j < MAXM; j++) {
      vals[j] = ((long long)vals[j] * other.vals[j]) % MODS[j];
    }
  }

  bool operator<(const ModNumber& other) const {
    for (int j = 0; j < MAXM; j++) {
      if (vals[j] != other.vals[j]) {
        return vals[j] < other.vals[j];
      }
    }
    return false;
  }

  bool operator==(const ModNumber& other) const {
    for (int j = 0; j < MAXM; j++) {
      if (vals[j] != other.vals[j]) {
        return false;
      }
    }
    return true;
  }
};

const int STEPS[MAXM] = {71, 71, 71};
ModNumber STEP;

const int MAXN = 2e5 + 5;
ModNumber pows[MAXN];

void init() {
  for (int j = 0; j < MAXM; j++) {
    pows[0].vals[j] = 1;
    STEP.vals[j] = STEPS[j];
  }

  for (int i = 1; i < MAXN; i++) {
    pows[i] = pows[i - 1];
    pows[i].mul(STEP);
  }
}

class Solver {
  int n;
  vector<vector<int>> adj;
  vector<int> a;

  vector<int> par;
  vector<ModNumber> sum;
  set<ModNumber> valid_hashs;
  map<pair<int, int>, ModNumber> dfs_val;

  ModNumber dfs(int u, int p) {
    auto itr = dfs_val.find({u, p});
    if (itr != dfs_val.end()) {
      return itr->second;
    }

    ModNumber h;
    if (par[u] != -1) {
      h = sum[u];
      if (par[u] != p) {
        h.add(dfs(par[u], u));
        h.sub(dfs(p, u));
      }
    } else {
      for (int v : adj[u]) {
        if (v == p) {
          continue;
        }
        h.add(dfs(v, u));
      }

      par[u] = p;
      sum[u] = h;
    }

    h.mul(STEP);
    h.add(pows[0]);

    dfs_val[{u, p}] = h;
    return h;
  }

 public:
  void read() {
    cin >> n;
    adj.resize(n + 1);
    a.resize(n - 1);

    for (int i = 0; i < n - 1; i++) {
      cin >> a[i];
    }

    for (int i = 0; i < n - 1; i++) {
      int u, v;
      cin >> u >> v;
      adj[u].push_back(v);
      adj[v].push_back(u);
    }
  }

  void solve() {
    ModNumber h;
    for (int val : a) {
      h.add(pows[val]);
    }
    for (int i = 0; i < n; i++) {
      ModNumber cur = h;
      cur.add(pows[i]);
      valid_hashs.insert(cur);
    }

    vector<int> ans;
    par.assign(n + 1, -1);
    sum.resize(n + 1);
    for (int u = 1; u <= n; u++) {
      ModNumber h;
      for (int v : adj[u]) {
        h.add(dfs(v, u));
      }
      h.mul(STEP);
      h.add(pows[0]);
      if (valid_hashs.count(h) > 0) {
        ans.push_back(u);
      }
    }

    cout << ans.size() << endl;
    for (int u : ans) {
      cout << u << ' ';
    }
    cout << endl;
  }
};

int main() {
  ios::sync_with_stdio(false);
  init();
  int t = 1;
  // cin >> t;
  while (t--) {
    Solver solver;
    solver.read();
    solver.solve();
  }
  return 0;
}
