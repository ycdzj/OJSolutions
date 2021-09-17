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
const long long INF = 1e18;

int abs(int x) {
    if(x < 0) {
        return -x;
    }
    return x;
}

struct Bit {
    vector<int> a;
    int n;

    static int lowbit(int x) {
        return x & (-x);
    }

    void init(int n_) {
        n = n_;
        a.resize(n + 1);
    }
    void update(int i, int diff) {
        while(i <= n) {
            a[i] += diff;
            i += lowbit(i);
        }
    }
    int query(int i) {
        int ans = 0;
        while(i >= 1) {
            ans += a[i];
            i -= lowbit(i);
        }
        return ans;
    }
};

class Solver {
    int n;
    vector<int> a;

    long long get_ans() {
        vector<int> b(n);
        for(int i = 0, cur[2] = {1, 2}; i < n; i++) {
            b[i] = cur[a[i]];
            cur[a[i]] += 2;
            if(b[i] > n) {
                return INF;
            }
        }

        Bit bit;
        bit.init(n);
        long long sum = 0;
        for(int i = n - 1; i >= 0; i--) {
            sum += bit.query(b[i] - 1);
            bit.update(b[i], 1);
        }
        return sum;
    }
public:
    void read() {
        Io::read(n);
        Io::read(a, n);
    }
    void solve() {
        for(int i = 0; i < n; i++) {
            a[i] &= 1;
        }
        long long ans = get_ans();
        for(int i = 0; i < n; i++) {
            a[i] ^= 1;
        }
        ans = min(ans, get_ans());
        if(ans == INF) {
            ans = -1;
        }
        Io::write(ans);
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
