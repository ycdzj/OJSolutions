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
const int MAXM = 61;

class Solver {
public:
    int n;
    vector<long long> a;
    void read() {
        IO::read(n);
        a.resize(n);
        for(int i = 0; i < n; i++) {
            IO::read(a[i]);
        }
    }
    void solve() {
        vector<int> cnt(MAXM);
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < MAXM; j++) {
                if(a[i] >> j & 1) {
                    cnt[j]++;
                }
            }
        }

        Mod mod(1e9 + 7);
        vector<int> p2(MAXM);
        p2[0] = 1;
        for(int i = 1; i < MAXM; i++) {
            p2[i] = mod.mul(p2[i - 1], 2);
        }

        int ans = 0;
        for(int j = 0; j < n; j++) {
            vector<int> cnt_or(MAXM);
            vector<int> cnt_and(MAXM);
            int l = 0, r = 0;
            for(int k = 0; k < MAXM; k++) {
                if(a[j] >> k & 1) {
                    cnt_or[k] = n;
                    cnt_and[k] = cnt[k];
                } else {
                    cnt_or[k] = cnt[k];
                    cnt_and[k] = 0;
                }

                l = mod.add(l, mod.mul(p2[k], cnt_and[k]));
                r = mod.add(r, mod.mul(p2[k], cnt_or[k]));
            }
            ans = mod.add(ans, mod.mul(l, r));
        }

        IO::write(ans);
    }
};

void init() {
    ios::sync_with_stdio(false);
}

int main() {
    init();

    int t = 1;
    IO::read(t);

    while (t--) {
        Solver solver;
        solver.read();
        solver.solve();
    }
    return 0;
}
