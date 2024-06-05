#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long ll;
const int MAXN = 5e5 + 6;
const int MAXM = 1e6 + 6;

struct Zkw {
    int tree[MAXM * 2];
    int n;
    void init(int n_) {
        n = n_;
        for(int i = 0; i < 2 * n; i++) tree[i] = 0;
    }
    void update(int p, int val) {
        tree[p += n] += val;
        for(p >>= 1; p > 0; p >>= 1) {
            tree[p] = tree[p << 1] + tree[p << 1 | 1];
        }
    }
    int query(int l, int r) {
        if(l > r) return 0;
        l += n; r += n;
        int res = tree[r];
        for(; l < r; l >>= 1, r >>= 1) {
            if(l & 1) res += tree[l++];
            if(r & 1) res += tree[--r];
        }
        return res;
    }

} zkw;

int n;
struct Cafe {
    ll x, y;
} cafe[MAXN];
bool cmp(Cafe a, Cafe b) {
    return a.x < b.x;
}
ll a, b, c, d, e, f, m;
int cnt[MAXN][2];

int main() {
    int T;
    scanf("%d", &T);
    for(int cnt_case = 1; cnt_case <= T; cnt_case++) {
        scanf("%d", &n);
        scanf("%lld%lld%lld%lld%lld%lld%lld%lld%lld", &cafe[0].x, &cafe[0].y, &a, &b, &c, &d, &e, &f, &m);
        for(int i = 1; i < n; i++) {
            cafe[i].x = (a * cafe[i - 1].x + b * cafe[i - 1].y + c) % m;
            cafe[i].y = (d * cafe[i - 1].x + e * cafe[i - 1].y + f) % m;
        }
        ll ans = (ll)n * (n - 1) * (n - 2) / 6;
        zkw.init(m);
        sort(cafe, cafe + n, cmp);
        for(int i = 0; i < n; ) {
            int nxt_i = i;
            while(nxt_i < n && cafe[nxt_i].x == cafe[i].x) {
                nxt_i++;
            }
            for(int j = i; j < nxt_i; j++) {
                cnt[j][0] = zkw.query(0, cafe[j].y - 1);
                cnt[j][1] = zkw.query(cafe[j].y + 1, m - 1);
            }
            for(int j = i; j < nxt_i; j++) {
                zkw.update(cafe[j].y, 1);
            }
            i = nxt_i;
        }
        zkw.init(m);
        for(int i = n - 1; i >= 0; ) {
            int nxt_i = i;
            while(nxt_i >= 0 && cafe[nxt_i].x == cafe[i].x) {
                nxt_i--;
            }
            for(int j = i; j > nxt_i; j--) {
                int cnt2 = zkw.query(0, cafe[j].y - 1);
                int cnt3 = zkw.query(cafe[j].y + 1, m - 1);
                ans -= (ll)cnt[j][0] * cnt3;
                ans -= (ll)cnt[j][1] * cnt2;
            }
            for(int j = i; j > nxt_i; j--) {
                zkw.update(cafe[j].y, 1);
            }
            i = nxt_i;
        }
        printf("Case #%d: %lld\n", cnt_case, ans);
    }
    return 0;
}