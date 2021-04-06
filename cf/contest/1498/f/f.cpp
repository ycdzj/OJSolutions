// ----------------------Template Start----------------------
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <algorithm>
#include <numeric>
#include <unordered_map>
#include <unordered_set>
#include <bitset>
using namespace std;
 
class Io {
public:
    static void read(int &val) { scanf("%d", &val); }
    static void read(long long &val) { scanf("%lld", &val); }
    static void read(char *val) { scanf("%s", val); }
    static void read(string &val) {
        const int BUFFER_SIZE = 2e6 + 5;
        static char buffer[BUFFER_SIZE];
        scanf("%s", buffer);
        val = buffer;
    }
    static void read(vector<int> &val, int n) {
        val.resize(n);
        for (int i = 0; i < n; i++) {
            scanf("%d", &val[i]);
        }
    }
    static void read(vector<long long> &val, int n) {
        val.resize(n);
        for (int i = 0; i < n; i++) {
            scanf("%lld", &val[i]);
        }
    }
 
    static void write(int val) { printf("%d\n", val); }
    static void write(long long val) { printf("%lld\n", val); }
    static void write(const char *val) { printf("%s\n", val); }
    static void write(const string &val) { printf("%s\n", val.c_str()); }
    static void write(const vector<int> &val) {
        for (int i = 0; i < val.size(); i++) {
            if (i > 0) {
                putchar(' ');
            }
            printf("%d", val[i]);
        }
        putchar('\n');
    }
    static void write(const vector<long long> &val) {
        for (int i = 0; i < val.size(); i++) {
            if (i > 0) {
                putchar(' ');
            }
            printf("%lld", val[i]);
        }
        putchar('\n');
    }
};
 
class Mod {
public:
    int mod;
 
    explicit Mod(int mod_) : mod(mod_) {}
 
    int add(int a, int b) const { return (a + b) % mod; }
    int sub(int a, int b) const { return (a + mod - b) % mod; }
    int mul(long long a, int b) const { return (a * b) % mod; }
    int pow(long long a, int x) const {
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
    int inv(int x) const {
        return pow(x, mod - 2);
    }
};
 
class Math {
public:
    static long long gcd_ex(long long a, long long b, long long &x, long long &y) {
        if (b == 0) {
            x = 1;
            y = 0;
            return a;
        }
        long long ans = gcd_ex(b, a % b, y, x);
        y -= (a / b) * x;
        return ans;
    }
};
 
class Combine {
    vector<int> fac;
    vector<int> inv_fac;
    Mod mod;
 
public:
    explicit Combine(int n, Mod mod_) : fac(n), inv_fac(n), mod(mod_) {
        fac[0] = 1;
        for (int i = 1; i < n; i++) {
            fac[i] = mod.mul(fac[i - 1], i);
        }
        inv_fac[n - 1] = mod.inv(fac[n - 1]);
        for (int i = n - 2; i >= 0; i--) {
            inv_fac[i] = mod.mul(inv_fac[i + 1], i + 1);
        }
    }
    int arrange(int n, int m) {
        if (n < m) {
            return 0;
        }
        return mod.mul(fac[n], inv_fac[n - m]);
    }
    int combine(int n, int m) {
        if (n < m) {
            return 0;
        }
        return mod.mul(arrange(n, m), inv_fac[m]);
    }
};
 
class Dsu {
    int n;
    vector<int> f;
 
public:
    explicit Dsu(int n_) : n(n_), f(n_) {
        for(int i = 0; i < f.size(); i++) {
            f[i] = i;
        }
    }
    int find(int x) {
        if(f[x] != x) {
            f[x] = find(f[x]);
        }
        return f[x];
    }
    void merge(int x, int y) {
        x = find(x);
        y = find(y);
        f[x] = y;
    }
};
 
// ----------------------Template End----------------------
class Solver {
    int n, k;
    vector<int> a;
    vector<pair<int, int>> edges;
    vector<vector<int>> adj;
    vector<queue<int>> que;

    vector<vector<int>> f;
    vector<vector<int>> sum_f;
    int get_f(int e, int x) {
        if(!f[e].empty()) {
            return f[e][x];
        }
        int par = edges[e].first;
        int u = edges[e].second;
        while(!que[u].empty()) {
            int nxt_e = que[u].front();
            que[u].pop();
            int v = edges[nxt_e].second;
            if(v == par) {
                que[u].push(nxt_e);
                if(que[u].size() == 1) {
                    break;
                }
                continue;
            }
            for(int y = 0; y < 2 * k; y++) {
                sum_f[u][y] ^= get_f(nxt_e, y);
            }
        }
        f[e].resize(2 * k);
        f[e][0] ^= a[u];
        for(int y = 0; y < 2 * k; y++) {
            int cur = sum_f[u][y];
            if(que[u].empty()) {
                cur ^= get_f(e ^ 1, y);
            }
            f[e][(y + 1) % (2 * k)] ^= cur;
        }
        return f[e][x];
    }
public:
    void read() {
        Io::read(n);
        Io::read(k);
        adj.resize(n);
        que.resize(n);
        for(int i = 1; i < n; i++) {
            int u, v;
            Io::read(u);
            Io::read(v);
            --u;
            --v;
            edges.emplace_back(u, v);
            adj[u].push_back(edges.size() - 1);
            que[u].push(edges.size() - 1);
            edges.emplace_back(v, u);
            adj[v].push_back(edges.size() - 1);
            que[v].push(edges.size() - 1);
        }
        Io::read(a, n);
    }
    void solve() {
        f.resize(edges.size());
        sum_f.resize(n);
        for(int i = 0; i < n; i++) {
            sum_f[i].resize(2 * k);
        }
        vector<int> ans_list;
        for(int u = 0; u < n; u++) {
            int ans = 0;
            for(int x = k - 1; x <= 2 * k - 2; x++) {
                for(int e : adj[u]) {
                    ans ^= get_f(e, x);
                }
            }
            if(ans != 0) {
                ans = 1;
            }
            ans_list.push_back(ans);
        }
        Io::write(ans_list);
    }
};
 
void init() {
    ios::sync_with_stdio(false);
}
 
int main() {
    init();
 
    int t = 1;
    //Io::read(t);
 
    while (t--) {
        Solver solver;
        solver.read();
        solver.solve();
    }
    return 0;
}
