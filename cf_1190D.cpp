#include <cstdio>
#include <set>
#include <algorithm>
using namespace std;

struct Point {
    int x, y;
};

bool cmp(Point a, Point b) {
    if(a.y == b.y) {
        return a.x < b.x;
    }
    return a.y > b.y;
}

const int MAXN = 2e5 + 5;
int n;
Point p[MAXN];
struct BIT {
    int tree[MAXN], n;
    int lowbit(int x) { return x & (-x); }
    void change(int p, int val) {
        while(p <= n) {
            tree[p] += val;
            p += lowbit(p);
        }
    }
    int query(int p) {
        int res = 0;
        while(p >= 1) {
            res += tree[p];
            p -= lowbit(p);
        }
        return res;
    }
} bit;

int buf[MAXN];
bool vis[MAXN];

int main() {
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        scanf("%d%d", &p[i].x, &p[i].y);
        buf[i] = p[i].x;
    }
    sort(p, p + n, cmp);
    sort(buf, buf + n);
    bit.n = n;

    long long ans = 0;
    for(int i = 0; i < n; i++) {
        int pos = lower_bound(buf, buf + n, p[i].x) - buf + 1 ;
        if(!vis[pos]) {
            vis[pos] = true;
            bit.change(pos, 1);
        }
        long long l = bit.query(pos);
        int cur = n;
        if(i != n - 1 && p[i].y == p[i + 1].y) {
            cur = lower_bound(buf, buf + n, p[i + 1].x) - buf;
        }
        long long r = bit.query(cur) - bit.query(pos - 1);
        ans += l * r;
    }
    printf("%lld\n", ans);
    return 0;
}
