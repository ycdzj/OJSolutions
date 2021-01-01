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

class Dsu {
public:
    int n;
    vector<int> f;

    Dsu(int n_) : n(n_), f(n_) {
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

class Solver {
public:
    int n, m;
    vector<vector<int>> edges;
    void read() {
        IO::read(n);
        IO::read(m);
        for(int i = 0; i < n; i++) {
            int sz;
            vector<int> a;
            IO::read(sz);
            IO::read_n(a, sz);
            if(a.size() == 1) {
                a.push_back(0);
            }
            if(a.size() == 2) {
                edges.push_back(a);
            }
        }
    }
    void solve() {
        vector<int> ans;
        Dsu dsu(m + 1);
        for(int i = 0; i < edges.size(); i++) {
            int u = edges[i][0];
            int v = edges[i][1];
            if(dsu.find(u) != dsu.find(v)) {
                ans.push_back(i + 1);
                dsu.merge(u, v);
            }
        }

        Mod mod(1e9 + 7);

        IO::write(vector<int>{mod.pow(2, ans.size()), (int)ans.size()});
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
