#include <algorithm>
#include <functional>
#include <ios>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

struct Interval {
  int l, r, t, p;
  bool operator < (const Interval& interval) const {
    if (l != interval.l) {
      return l < interval.l;
    }
    return r < interval.r;
  }
};

struct SInterval {
  int l, r, t, p;
  explicit SInterval(Interval i) : l(i.l), r(i.r), t(i.t), p(i.p) {}
  bool operator < (const SInterval& interval) const {
    return r < interval.r;
  }
};

struct Rain {
  int x, p, idx;
  bool operator < (const Rain& rain) const {
    return x < rain.x;
  }
};

struct Bit {
  static int lowbit(int x) {
    return x & (-x);
  }

  vector<int> a_;
  int n_;
  explicit Bit(int n) : a_(n + 1), n_(n) {}
  void update(int p, int x) {
    p++;
    while(p <= n_) {
      a_[p] += x;
      p += lowbit(p);
    }
  }
  int get(int p) {
    p++;
    int ret = 0;
    while(p >= 1) {
      ret += a_[p];
      p -= lowbit(p);
    }
    return ret;
  }
};

struct Solver {
  int n, m;
  vector<Rain> rains;

  void read() {
    cin >> n >> m;
    rains.resize(n);
    for (int i = 0; i < n; i++) {
      cin >> rains[i].x >> rains[i].p;
      rains[i].idx = i;
    }
  }

  std::vector<long long> get_total_rain() {
    vector<Interval> intervals;
    for (const auto& rain : rains) {
      int x = rain.x;
      int p = rain.p;
      intervals.push_back({x - p + 1, x, 0, p});
      if (p > 1) {
        intervals.push_back({x + 1, x + p - 1, 1, p - 1});
      }
    }
    sort(intervals.begin(), intervals.end());
    multiset<SInterval> s[2];
    long long cur_rain = 0;
    int pos = 0;
    vector<long long> total_rain(n);
    for (int i = 0; i < n; i++) {
      int x = rains[i].x;
      for (; pos < intervals.size() && intervals[pos].l <= x; pos++) {
        if (intervals[pos].r < x) {
          continue;
        }
        if (intervals[pos].t == 0) {
          cur_rain += x - intervals[pos].l + 1;
        } else {
          cur_rain += intervals[pos].p - (x - intervals[pos].l);
        }
        s[intervals[pos].t].insert(SInterval(intervals[pos]));
      }
      total_rain[i] = cur_rain;
      if (i + 1 < n) {
        for (int t = 0; t < 2; t++) {
          while (!s[t].empty() && s[t].begin()->r < rains[i + 1].x) {
            if (t == 0) {
              cur_rain -= x - s[t].begin()->l + 1;
            } else {
              cur_rain -= s[t].begin()->p - (x - s[t].begin()->l);
            }
            s[t].erase(s[t].begin());
          }
        }
        long long diff = rains[i + 1].x - x;
        cur_rain += diff * s[0].size();
        cur_rain -= diff * s[1].size();
      }
    }
    return total_rain;
  }

  std::vector<int> get_idx_by_p_plus_x() {
    std::vector<int> idx(n);
    for (int i = 0; i < n; i++) {
      idx[i] = i;
    }
    sort(idx.begin(), idx.end(), [this](int a, int b) { return rains[a].x + rains[a].p < rains[b].x + rains[b].p; });
    return idx;
  }

  std::vector<int> get_idx_by_p_minus_x() {
    std::vector<int> idx(n);
    for (int i = 0; i < n; i++) {
      idx[i] = i;
    }
    sort(idx.begin(), idx.end(), [this](int a, int b) { return rains[a].p - rains[a].x < rains[b].p - rains[b].x; });
    return idx;
  }

  int lower_bound_by_p_plus_x(const std::vector<int>& idx, long long val) {
    int l = 0, r = n;
    while(l < r) {
      int mid = l + (r - l) / 2;
      if (rains[idx[mid]].x + rains[idx[mid]].p < val) {
        l = mid + 1;
      } else {
        r = mid;
      }
    }
    return l;
  }

  int lower_bound_by_p_minus_x(const std::vector<int>& idx, long long val) {
    int l = 0, r = n;
    while(l < r) {
      int mid = l + (r - l) / 2;
      if (rains[idx[mid]].p - rains[idx[mid]].x < val) {
        l = mid + 1;
      } else {
        r = mid;
      }
    }
    return l;
  }

  std::vector<int> get_rev_idx(const std::vector<int>& idx) {
    std::vector<int> rev_idx(n);
    for (int i = 0; i < n; i++) {
      rev_idx[idx[i]] = i;
    }
    return rev_idx;
  }

  void solve() {
    sort(rains.begin(), rains.end());
    std::vector<long long> total_rain = get_total_rain();
    std::vector<int> idx_by_p_plus_x = get_idx_by_p_plus_x();
    std::vector<int> rev_idx_by_p_plus_x = get_rev_idx(idx_by_p_plus_x);
    Bit bit(n + 1);
    bit.update(0, -n - 10);
    for (int i = 0; i < n; i++) {
      if (i + 1 < n && rains[i].x == rains[i + 1].x) {
        continue;
      }
      if (total_rain[i] > m) {
        int pos = lower_bound_by_p_plus_x(idx_by_p_plus_x, total_rain[i] - m + rains[i].x);
        bit.update(pos, 1);
      }
      for (int j = i; j >= 0 && rains[j].x == rains[i].x; j--) {
        int val = bit.get(rev_idx_by_p_plus_x[j]);
        bit.update(rev_idx_by_p_plus_x[j], -val);
        bit.update(rev_idx_by_p_plus_x[j] + 1, val);
      }
    }

    std::vector<int> cnt_solved(n);
    for (int i = 0; i < n; i++) {
      int val = bit.get(rev_idx_by_p_plus_x[i]);
      if (val >= 0) {
        cnt_solved[i] += val;
      }
    }

    std::vector<int> idx_by_p_minus_x = get_idx_by_p_minus_x();
    std::vector<int> rev_idx_by_p_minus_x = get_rev_idx(idx_by_p_minus_x);
    bit.update(0, -n - 10);
    int cnt_bad = 0;
    for (int i = n - 1; i >= 0; i--) {
      if (i - 1 >= 0 && rains[i - 1].x == rains[i].x) {
        continue;
      }
      if (total_rain[i] > m) {
        cnt_bad++;
        int pos = lower_bound_by_p_minus_x(idx_by_p_minus_x, total_rain[i] - m - rains[i].x);
        bit.update(pos, 1);
      }
      for (int j = i; j < n && rains[j].x == rains[i].x; j++) {
        int val = bit.get(rev_idx_by_p_minus_x[j]);
        bit.update(rev_idx_by_p_minus_x[j], -val);
        bit.update(rev_idx_by_p_minus_x[j] + 1, val);
      }
    }

    vector<int> ans(n);
    for (int i = 0; i < n; i++) {
      int val = bit.get(rev_idx_by_p_minus_x[i]);
      if (val >= 0) {
        cnt_solved[i] += val;
      }
      if (total_rain[i] > m) {
        if (total_rain[i] - rains[i].p <= m) {
          cnt_solved[i]++;
        }
      }
      if (cnt_solved[i] == cnt_bad) {
        ans[rains[i].idx] = 1;
      }
    }

    for (int i = 0; i < n; i++) {
      cout << ans[i];
    }
    cout << endl;
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
