// ----------------------Template Start----------------------
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <algorithm>
#include <numeric>
using namespace std;

class Mod {
public:
    int mod;

    Mod(int mod_ = 1e9 + 7) : mod(mod_) {}

    int add(int a, int b) { return (a + b) % mod; }
    int mul(long long a, int b) { return (a * b) % mod; }
    int pow(long long a, int x) {
        int ans = 1;
        while (x) {
            if (x & 1) {
                ans = (ans * a) % mod;
            }
            x >>= 1;
            a = (a * a) % mod;
        }
        return ans;
    }
};
Mod mod;

// ----------------------Template End----------------------

struct Item {
    int t, x, y;
};

class Solver {
    int r, n;
    vector<Item> item_list;

    int abs(int x) {
        if(x < 0) {
            x = -x;
        }
        return x;
    }
    int get_dis(int i, int j) {
        return abs(item_list[i].x - item_list[j].x) + abs(item_list[i].y - item_list[j].y);
    }
public:
    void read() {
        scanf("%d%d", &r, &n);
        item_list.resize(n);
        for(int i = 0; i < n; i++) {
            scanf("%d%d%d", &item_list[i].t, &item_list[i].x, &item_list[i].y);
        }
    }
    void solve() {
        vector<int> f(n), max_f(n);
        int ans = 0;
        for(int i = n - 1; i >= 0; i--) {
            f[i] = 1;
            for(int j = i + 1; j < n; j++) {
                int dis = get_dis(i, j);
                if(dis <= item_list[j].t - item_list[i].t) {
                    f[i] = max(f[i], 1 + f[j]);
                }
                if(item_list[j].t - item_list[i].t >= 2 * r) {
                    f[i] = max(f[i], 1 + max_f[j]);
                    break;
                }
            }
            max_f[i] = f[i];
            if(i + 1 < n) {
                max_f[i] = max(max_f[i], max_f[i + 1]);
            }
            if(item_list[i].x + item_list[i].y - 2 <= item_list[i].t) {
                ans = max(ans, f[i]);
            }
        }
        printf("%d\n", ans);
    }
};

void init() {
    ios::sync_with_stdio(false);
}

int main() {
    init();

    int t = 1;
    //scanf("%d", &t);

    while(t--) {
        Solver solver;
        solver.read();
        solver.solve();
    }
    return 0;
}
