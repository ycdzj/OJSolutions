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
const int MAXM = 5e6 + 5;

class Solver {
    int n;
    vector<int> a;

    bool check(const vector<int> &indices) {
        for(int i = 0; i < 2; i++) {
            for(int j = 2; j < 4; j++) {
                if(indices[i] == indices[j]) {
                    return false;
                }
            }
        }
        if(a[indices[0]] + a[indices[1]] == a[indices[2]] + a[indices[3]]) {
            vector<int> b(indices);
            for(int &val : b) {
                val++;
            }
            Io::write("YES");
            Io::write(b);
            return true;
        }
        return false;
    }

    vector<int> vis;
    int clk;
    bool check(const vector<pair<int, int>> &indices) {
        for(int i = 0; i < indices.size(); i++) {
            for(int j = i + 1; j < indices.size(); j++) {
                if(check({indices[i].first, indices[i].second, indices[j].first, indices[j].second})) {
                    return true;
                }
            }
        }
        if(indices.size() >= 3) {
            vector<int> pos;
            clk++;
            for(int i = 0; i < indices.size(); i++) {
                if(vis[indices[i].first] != clk) {
                    vis[indices[i].first] = clk;
                    pos.push_back(indices[i].first);
                }
                if(vis[indices[i].second] != clk) {
                    vis[indices[i].second] = clk;
                    pos.push_back(indices[i].second);
                }
            }
            for(int i = 0; i < pos.size(); i++) {
                for(int j = i + 1; j < pos.size(); j++) {
                    for(int k = j + 1; k < pos.size(); k++) {
                        for(int l = k + 1; l < pos.size(); l++) {
                            if(a[pos[i]] + a[pos[l]] == a[pos[j]] + a[pos[k]]) {
                                Io::write("YES");
                                Io::write(vector<int>{pos[i] + 1, pos[l] + 1, pos[j] + 1, pos[k] + 1});
                                return true;
                            }
                        }
                    }
                }
            }
        }
        return false;
    }

public:
    void read() {
        Io::read(n);
        Io::read(a, n);
    }
    void solve() {
        vector<vector<pair<int, int>>> b(MAXM);
        vis.resize(n);
        for(int i = 0; i < n; i++) {
            for(int j = i + 1; j < n; j++) {
                int s = a[i] + a[j];
                b[s].push_back({i, j});
                if(check(b[s])) {
                    return;
                }
            }
        }
        Io::write("NO");
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
