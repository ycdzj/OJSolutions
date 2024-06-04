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
struct Edge {
    int u, v, w;
};
class Solver {
    int n, m;
    vector<vector<Edge>> adj;
    vector<Edge> edges;
    int xor_sum;
    
    vector<bool> get_vis(const vector<Edge> &adj_u) {
        vector<bool> vis(n + 1);
        for(auto e : adj_u) {
            vis[e.v] = true;
        }
        return vis;
    }
    long long mst_update(Dsu &dsu, Edge e) {
        int u = dsu.find(e.u);
        int v = dsu.find(e.v);
        if(u == v) {
            return 0;
        }
        dsu.merge(u, v);
        return e.w;
    }
    long long get_mst(int idx) {
        Dsu dsu(n + 1);
        for(int i = m; i < edges.size(); i++) {
            if(i == idx) {
                continue;
            }
            dsu.merge(edges[i].u, edges[i].v);
        }
        long long ans = 0;
        bool flag = false;
        for(int i = 0; i < m; i++) {
            if(!flag && edges[i].w >= edges[idx].w) {
                ans += mst_update(dsu, edges[idx]);
                flag = true;
            }
            ans += mst_update(dsu, edges[i]);
        }
        return ans;
    }
    void solve1() {
        vector<vector<int>> adj_mat(n + 1);
        for(int i = 1; i <= n; i++) {
            adj_mat[i].assign(n + 1, -1);
            for(auto e : adj[i]) {
                adj_mat[i][e.v] = e.w;
            }
        }
        for(int i = 1; i <= n; i++) {
            for(int j = i + 1; j <= n; j++) {
                if(adj_mat[i][j] == -1) {
                    edges.push_back({i, j, 0});
                }
            }
        }
        long long ans = 1e18;
        for(int i = m; i < edges.size(); i++) {
            edges[i].w = xor_sum;
            ans = min(ans, get_mst(i));
            edges[i].w = 0;
        }
        Io::write(ans);
    }
    void solve2() {
        int u = 1;
        for(int i = 2; i <= n; i++) {
            if(adj[i].size() < adj[u].size()) {
                u = i;
            }
        }
        Dsu dsu(n + 1);
        vector<bool> vis = get_vis(adj[u]);
        for(int i = 1; i <= n; i++) {
            if(!vis[i]) {
                dsu.merge(i, u);
            }
        }
        for(auto e : adj[u]) {
            vis = get_vis(adj[e.v]);
            for(int i = 1; i <= n; i++) {
                if(!vis[i]) {
                    dsu.merge(i, e.v);
                }
            }
        }
        long long ans = 0;
        for(auto e : edges) {
            xor_sum ^= e.w;
            int u = dsu.find(e.u);
            int v = dsu.find(e.v);
            if(u != v) {
                dsu.merge(u, v);
                ans += e.w;
            }
        }
        Io::write(ans);
    }
public:
    void read() {
        Io::read(n);
        Io::read(m);
        adj.resize(n + 1);
        for(int i = 0; i < m; i++) {
            int u, v, w;
            Io::read(u);
            Io::read(v);
            Io::read(w);
            adj[u].push_back({u, v, w});
            adj[v].push_back({v, u, w});
            edges.push_back({u, v, w});
        }
    }
    void solve() {
        sort(edges.begin(), edges.end(), [](Edge a, Edge b){
            return a.w < b.w;
        });
        xor_sum = 0;
        for(auto e : edges) {
            xor_sum ^= e.w;
        }

        if((long long)n * (n - 1) / 2 - m <= n - 1) {
            solve1();
        } else {
            solve2();
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
