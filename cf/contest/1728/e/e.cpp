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

long long exgcd(long long a, long long b, long long& x, long long &y) {
  if (b == 0) {
    x = 1;
    y = 0;
    return a;
  }
  long long g = exgcd(b, a % b, y, x);
  y -= (a / b) * x;
  return g;
}

class Solver {
  long long n, m;
  vector<long long> a, b, x, y;

 public:
  void read() {
    cin >> n;
    a.resize(n);
    b.resize(n);
    for (int i = 0; i < n; i++) {
      cin >> a[i] >> b[i];
    }

    cin >> m;
    x.resize(m);
    y.resize(m);
    for (int i = 0; i < m; i++) {
      cin >> x[i] >> y[i];
    }
  }

  void solve() {
    vector<long long> d(n);
    long long sum_b = 0;
    for (int i = 0; i < n; i++) {
      d[i] = a[i] - b[i];
      sum_b += b[i];
    }
    sort(d.rbegin(), d.rend());

    vector<long long> sum(n + 1);
    long long p = 0;
    for (int i = 1; i <= n; i++) {
      sum[i] = d[i - 1] + sum[i - 1];
      if (d[i - 1] >= 0) {
        p++;
      }
    }

    for (int i = 0; i < m; i++) {
      long long aa, bb;
      long long g = exgcd(x[i], y[i], aa, bb);
      if (n % g != 0) {
        cout << -1 << endl;
        continue;
      }
      aa *= n / g;
      bb *= n / g;

      long long ans = -1;

      long long k = (p - x[i] * aa) * g / (x[i] * y[i]);
      long long aaa = aa + k * y[i] / g;
      if (aaa >= 0 && aaa * x[i] <= n) {
        ans = max(ans, sum_b + sum[aaa * x[i]]);
      }

      k++;
      aaa = aa + k * y[i] / g;
      if (aaa >= 0 && aaa * x[i] <= n) {
        ans = max(ans, sum_b + sum[aaa * x[i]]);
      }

      k -= 2;
      aaa = aa + k * y[i] / g;
      if (aaa >= 0 && aaa * x[i] <= n) {
        ans = max(ans, sum_b + sum[aaa * x[i]]);
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
