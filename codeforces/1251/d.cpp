#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;
const int MAXN = 2e5 + 5;
struct Interval {
    int l, r;
};

struct Oper {
    int val, idx, type;
    bool operator < (const Oper &op) const {
        return val < op.val;
    }
};

int n;
long long s;
Interval intervals[MAXN];

struct Query {
    multiset<int> sl, sr;
    long long sum_l = 0;
    void insert(int val) {
        sl.insert(val);
        sum_l += val;
    }
    void del(int val) {
        auto itr = sr.find(val);
        if(itr != sr.end()) {
            sr.erase(itr);
        }
        else {
            sl.erase(sl.find(val));
            sum_l -= val;
            if(!sr.empty()) {
                itr = sr.begin();
                sl.insert(*itr);
                sum_l += *itr;
                sr.erase(itr);
            }
        }
    }
    long long query(int cnt) {
        while(sl.size() > cnt) {
            auto itr = --sl.end();
            sum_l -= *itr;
            sr.insert(*itr);
            sl.erase(itr);
        }
        return sum_l;
    }
};

int main() {
    int t;
    scanf("%d", &t);
    while(t--) {
        scanf("%d%lld", &n, &s);
        vector<Oper> ops;
        for(int i = 0; i < n; i++) {
            int l, r;
            scanf("%d%d", &l, &r);
            intervals[i].l = l;
            intervals[i].r = r;
            ops.push_back({l, i, 0});
            ops.push_back({r + 1, i, 1});
        }
        sort(ops.begin(), ops.end());
        int cnt_r = n, cnt_l = 0;
        long long sum_l = 0, sum_r = 0;
        for(int i = 0; i < n; i++) {
            sum_r += intervals[i].l;
        }
        Query q;
        long long ans = 0;
        for(int i = 0; i + 1 < ops.size(); i++) {
            int val = intervals[ops[i].idx].l;
            if(ops[i].type == 0) {
                cnt_r--;
                sum_r -= val;
                q.insert(val);
            }
            else {
                q.del(val);
                cnt_l++;
                sum_l += val;
            }
            long long l = ops[i].val, r = ops[i + 1].val - 1;
            if(l <= r && cnt_l <= n / 2 && cnt_r <= n / 2) {
                long long cur = sum_r + sum_l + q.query(n / 2 - cnt_l);
                int cnt_y = n - cnt_r - n / 2;
                long long cur_val = (s - cur) / cnt_y;
                if(l <= cur_val) {
                    ans = max(ans, min(cur_val, r));
                }
            }
        }
        printf("%lld\n", ans);
    }
    return 0;
}

