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
    int l, r;
public:
    void read() {
        Io::read(l);
        Io::read(r);
    }
    void solve() {
        int len = r - l + 1;

        int n = 1;
        vector<vector<pair<int, int>>> adj(n);
        for(int cur_len = 1; cur_len <= len; cur_len *= 2) {
            n++;
            adj.emplace_back();

            adj[n - 1] = adj[n - 2];
            adj[n - 1].push_back({n - 2, (cur_len + 1) / 2});
        }

        if((1 << (n - 2)) < len) {
            n++;
            adj.emplace_back();
            for(int i = n - 2, cur_len = len; cur_len > 0 && i > 0; i--) {
                int node_len = (1 << (i - 1));
                if(node_len > cur_len) {
                    continue;
                }
                if(node_len == cur_len) {
                    adj[n - 1].insert(adj[n - 1].end(), adj[i].begin(), adj[i].end());
                } else {
                    int dis = cur_len - node_len;
                    adj[n - 1].push_back({i, dis});
                }
                cur_len -= node_len;
            }
        }

        if(l > 1) {
            n++;
            adj.emplace_back();
            adj[n - 1].push_back({n - 2, l - 1});
        }

        Io::write("YES");
        int m = 0;
        for(int i = 0; i < n; i++) {
            m += adj[i].size();
        }
        Io::write(vector<int>{n, m});
        for(int u = 0; u < n; u++) {
            for(auto pr : adj[u]) {
                int v = pr.first;
                int w = pr.second;
                Io::write(vector<int>{n - u, n - v, w});
            }
        }
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
