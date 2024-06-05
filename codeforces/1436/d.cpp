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

class IO {
public:
    static void read(int &val) { scanf("%d", &val); }
    static void read(long long &val) { scanf("%lld", &val); }
    static void read(char *val) { scanf("%s", val); }
    static void read(string &val) {
        const int BUFFER_SIZE = 1e5 + 5;
        static char buffer[BUFFER_SIZE];
        scanf("%s", buffer);
        val = buffer;
    }
    static void read_n(vector<int> &val, int n) {
        val.resize(n);
        for (int i = 0; i < n; i++) {
            scanf("%d", &val[i]);
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
};

class Mod {
public:
    int mod;

    explicit Mod(int mod_) : mod(mod_) {}

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
    int inv(int x) {
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

// ----------------------Template End----------------------

class Solver {
    int n;
    vector<vector<int>> adj;
    vector<int> a;
    long long ans = 0;

    void dfs(int u, int par, int &cnt_leaf, long long &sum) {
        cnt_leaf = 0;
        sum = a[u];
        for(int v : adj[u]) {
            if(v == par) {
                continue;
            }
            int cur_cnt_leaf;
            long long cur_sum;
            dfs(v, u, cur_cnt_leaf, cur_sum);
            cnt_leaf += cur_cnt_leaf;
            sum += cur_sum;
        }
        if(cnt_leaf == 0) {
            cnt_leaf = 1;
        }
        ans = max(ans, (sum + cnt_leaf - 1) / cnt_leaf);
    }
public:
    void read() {
        IO::read(n);
        adj.resize(n + 1);
        for(int i = 2; i <= n; i++) {
            int j;
            IO::read(j);
            adj[i].push_back(j);
            adj[j].push_back(i);
        }
        a.resize(n + 1);
        for(int i = 1; i <= n; i++) {
            IO::read(a[i]);
        }
    }
    void solve() {
        int cnt_leaf;
        long long sum;
        dfs(1, 1, cnt_leaf, sum);
        IO::write(ans);
    }
};

void init() {
    ios::sync_with_stdio(false);
}

int main() {
    init();

    int t = 1;
    //IO::read(t);

    while (t--) {
        Solver solver;
        solver.read();
        solver.solve();
    }
    return 0;
}