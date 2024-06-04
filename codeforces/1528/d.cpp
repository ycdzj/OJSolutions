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
    static void write(double val) { printf("%.8f\n", val); }
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
    static void write(const vector<double> &val) {
        for (int i = 0; i < val.size(); i++) {
            if (i > 0) {
                putchar(' ');
            }
            printf("%.8f", val[i]);
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
    static long long gcd(long long a, long long b) {
        long long x, y;
        return gcd_ex(a, b, x, y);
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
    struct Edge {
        int b, c;
    };
    int n, m;
    vector<vector<Edge>> adj;
    vector<long long> dis;
    vector<bool> vis;

    void get_dis(int s) {
        dis.assign(n, 1e18);
        vis.assign(n, false);
        dis[s] = 0;
        while(true) {
            int u = -1;
            long long dis_u = 1e18;
            for(int i = 0; i < n; i++) {
                if(vis[i]) {
                    continue;
                }
                if(dis[i] < dis_u) {
                    dis_u = dis[i];
                    u = i;
                }
            }
            if(u == -1) {
                break;
            }
            vis[u] = true;
            vector<Edge> adj_u = adj[u];
            for(auto &e : adj_u) {
                e.b = (e.b + dis_u) % n;
            }
            static vector<long long> min_c;
            min_c.assign(n, 1e18);
            for(int i = 0; i < adj_u.size(); ) {
                int j = i;
                while(j < adj_u.size() && adj_u[j].c == adj_u[i].c) {
                    j++;
                }
                int nxt_i = j;
                for(int k = j - 1; k >= i; k--) {
                    if(adj_u[k].c < min_c[adj_u[k].b]) {
                        min_c[adj_u[k].b] = adj_u[k].c;
                        adj_u[k].b = (adj_u[k].b + 1) % n;
                        adj_u[k].c++;
                        adj_u[--nxt_i] = adj_u[k];
                    }
                }
                i = nxt_i;
            }
            for(int i = 0; i < n; i++) {
                if(dis_u + min_c[i] < dis[i]) {
                    dis[i] = dis_u + min_c[i];
                }
            }
        }
    }
public:
    void read() {
        Io::read(n);
        Io::read(m);
        adj.resize(n);
        for(int i = 0; i < m; i++) {
            int a, b, c;
            Io::read(a);
            Io::read(b);
            Io::read(c);
            adj[a].push_back({b, c});
        }
    }
    void solve() {
        for(int u = 0; u < n; u++) {
            sort(adj[u].begin(), adj[u].end(), [](Edge x, Edge y) {
                return x.c < y.c;
            });
        }
        for(int s = 0; s < n; s++) {
            get_dis(s);
            Io::write(dis);
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
