#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
const int MAXN = 5e5 + 5;
struct Basis {
    int bas[20];
    void insert(int x) {
        for(int i = 19; i >= 0; i--) if(x >> i & 1) {
            if(bas[i]) x ^= bas[i];
            else {
                bas[i] = x;
                return;
            }
        }
    }
    void init() {
        memset(bas, 0, sizeof(bas));
    }
} basis[MAXN], tmp;

int lpos[MAXN], rpos[MAXN], ans[MAXN];
int n, q;
int c[MAXN];
void solve(int l, int r, vector<int> &v) {
    if(l == r) {
        for(auto val : v) ans[val] = c[l];
    }
    else {
        int mid = (l + r) / 2;
        vector<int> vl, vr;
        for(auto val : v) {
            if(rpos[val] <= mid) vl.push_back(val);
            else if(mid + 1 <= lpos[val]) vr.push_back(val);
        }
        solve(l, mid, vl);
        solve(mid + 1, r, vr);

        basis[mid].init();
        basis[mid].insert(c[mid]);
        for(int i = mid - 1; i >= l; i--) {
            basis[i] = basis[i + 1];
            basis[i].insert(c[i]);
        }

        basis[mid + 1].init();
        basis[mid + 1].insert(c[mid + 1]);
        for(int i = mid + 2; i <= r; i++) {
            basis[i] = basis[i - 1];
            basis[i].insert(c[i]);
        }

        for(auto val : v) {
            if(lpos[val] <= mid && mid + 1 <= rpos[val]) {
                tmp.init();
                for(int i = 0; i < 20; i++) {
                    tmp.insert(basis[lpos[val]].bas[i]);
                    tmp.insert(basis[rpos[val]].bas[i]);
                }
                int x = 0;
                for(int i = 19; i >= 0; i--) {
                    if((x >> i & 1) == 0) x ^= tmp.bas[i];
                }
                ans[val] = x;
            }
        }

    }
}
int main() {
    scanf("%d", &n);
    for(int i = 0; i < n; i++) scanf("%d", &c[i]);
    scanf("%d", &q);

    vector<int> v;
    for(int i = 0; i < q; i++) {
        scanf("%d%d", &lpos[i], &rpos[i]);
        --lpos[i];
        --rpos[i];
        v.push_back(i);
    }
    solve(0, n - 1, v);
    for(int i = 0; i < q; i++) printf("%d\n", ans[i]);
    return 0;
}