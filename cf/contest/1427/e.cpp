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
#include <sstream>
using namespace std;

class Mod {
public:
    int mod;

    Mod(int mod_ = 1e9 + 7) : mod(mod_) {}

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
};

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

long long gcd_ex(long long a, long long b, long long &x, long long &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    long long ans = gcd_ex(b, a % b, y, x);
    y -= (a / b) * x;
    return ans;
}

// ----------------------Template End----------------------

class Solver {
    long long x;
    stringstream ans;
    int cnt_ans = 0;
    void print(long long x, long long a) {
        long long cur = 0;
        while (a) {
            if (a & 1) {
                if (cur > 0) {
                    ans << cur << " + " << x << endl;
                    cnt_ans++;
                }
                cur += x;
            }
            a >>= 1;
            ans << x << " + " << x << endl;
            cnt_ans++;
            x <<= 1;
        }
    }

public:
    void read() {
        IO::read(x);
    }
    void solve() {
        long long e = 1;
        while ((e << 1) <= x) {
            e <<= 1;
        }
        print(x, e);
        ans << e * x << " ^ " << x << endl;
        cnt_ans++;
        long long y = ((e * x) ^ x);
        long long a, b;
        gcd_ex(x, y, a, b);
        if (a < 0) {
            swap(a, b);
            swap(x, y);
        }
        b = -b;
        if (!(a & 1)) {
            a += y;
            b += x;
        }
        print(x, a);
        print(y, b);
        ans << a * x << " ^ " << b * y << endl;
        cnt_ans++;

        IO::write(cnt_ans);
        IO::write(ans.str());
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
