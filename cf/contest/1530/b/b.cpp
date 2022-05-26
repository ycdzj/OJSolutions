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
    int h, w;
    vector<vector<int>> board;
    bool check(int i, int j) {
        for(int x = -1; x <= 1; x++) {
            for(int y = -1; y <= 1; y++) {
                int cur_i = i + x;
                int cur_j = j + y;
                if(0 <= cur_i && cur_i < h) {
                    if(0 <= cur_j && cur_j < w) {
                        if(board[cur_i][cur_j] == 1) {
                            return false;
                        }
                    }
                }
            }
        }
        return true;
    }
public:
    void read() {
        Io::read(h);
        Io::read(w);
    }
    void solve() {
        board.assign(h, vector<int>(w));
        board[0][0] = 1;
        board[0][w - 1] = 1;
        board[h - 1][0] = 1;
        board[h - 1][w - 1] = 1;
        for(int i = 0; i < h; i++) {
            if(check(i, 0)) {
                board[i][0] = 1;
            }
            if(check(i, w - 1)) {
                board[i][w - 1] = 1;
            }
        }
        for(int j = 0; j < w; j++) {
            if(check(0, j)) {
                board[0][j] = 1;
            }
            if(check(h - 1, j)) {
                board[h - 1][j] = 1;
            }
        }
        for(int i = 0; i < h; i++) {
            for(int j = 0; j < w; j++) {
                printf("%d", board[i][j]);
            }
            printf("\n");
        }
    }
};
 
void init() {
    ios::sync_with_stdio(false);
}
 
int main() {
    init();
 
    int t = 1;
    Io::read(t);
 
    while (t--) {
        Solver solver;
        solver.read();
        solver.solve();
    }
    return 0;
}
