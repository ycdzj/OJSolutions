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
        const int BUFFER_SIZE = 1e6 + 5;
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

const int MAXM = 1e6 + 5;

vector<int> get_kmp_next(const string &str) {
    vector<int> nxt(str.size());
    nxt[0] = -1;
    for(int i = 1; i < str.size(); i++) {
        int cur = nxt[i - 1];
        while(cur != -1 && str[cur + 1] != str[i]) {
            cur = nxt[cur];
        }
        if(str[cur + 1] == str[i]) {
            cur++;
        }
        nxt[i] = cur;
    }
    return nxt;
}

vector<int> get_idx_list(const string &aa, const string &bb) { // a: prefix, b: suffix
    string a, b;
    if(aa.length() < bb.length()) {
        a = aa;
        b = bb.substr(bb.length() - aa.length(), aa.length());
    } else if(aa.length() > bb.length()) {
        a = aa.substr(0, bb.length());
        b = bb;
    } else {
        a = aa;
        b = bb;
    }

    vector<int> nxt_of_a = get_kmp_next(a);

    int pre = -1;
    for(int i = 0; i < b.size(); i++) {
        int cur = ((pre == (int)a.size() - 1) ? (nxt_of_a[pre]) : (pre));
        while(cur != -1 && a[cur + 1] != b[i]) {
            cur = nxt_of_a[cur];
        }
        if(a[cur + 1] == b[i]) {
            cur++;
        }
        pre = cur;
    }

    vector<int> ret;
    for(int i = pre; i != -1; i = nxt_of_a[i]) {
        ret.push_back(i);
    }
    return ret;
}

int count_occurrences(const string &text, const string &pattern) {
    vector<int> nxt = get_kmp_next(pattern);
    int ans = 0;
    for(int pre = -1, i = 0; i < text.size(); i++) {
        while(pre != -1 && pattern[pre + 1] != text[i]) {
            pre = nxt[pre];
        }
        if(pattern[pre + 1] == text[i]) {
            pre++;
        }
        if(pre == pattern.size() - 1) {
            ans++;
            pre = nxt[pre];
        }
    }
    return ans;
}

Mod mod{(int)1e9 + 7};
vector<int> p2, p2_inv;

class Solver {
    int n, q;
    vector<string> s;
    string t;
    vector<pair<string, int>> queries;
    vector<vector<int>> h;

    tuple<vector<int>, vector<int>> get_pre_suf(const std::string &w, int j) {
        vector<int> prefix_idx_list = get_idx_list(w, s[j]);
        vector<int> suffix_idx_list = get_idx_list(s[j], w);

        vector<int> prefix(w.size() + 1), suffix(w.size() + 1);
        for(int idx : prefix_idx_list) {
            prefix[idx + 1] = 1;
        }
        for(int idx : suffix_idx_list) {
            suffix[idx + 1] = 1;
        }
        prefix[0] = 1;
        suffix[0] = 1;

        return make_tuple(prefix, suffix);
    }

    int get_g(const string &w, int j) {
        vector<int> prefix, suffix;
        tie(prefix, suffix) = get_pre_suf(w, j);

        int ans = 0;
        for(int x = 0; x < w.size(); x++) {
            ans += prefix[x] * suffix[w.size() - x - 1] * ((t[j] == w[x]) ? 1 : 0);
        }
        return ans;
    }

public:
    void read() {
        s.resize(1);

        Io::read(n);
        Io::read(q);
        Io::read(s[0]);
        Io::read(t);

        queries.resize(q);
        for(int i = 0; i < q; i++) {
            Io::read(queries[i].second);
            Io::read(queries[i].first);
        }
    }
    void solve() {
        while(s.back().length() < MAXM) {
            int idx = s.size() - 1;
            if(idx >= n) {
                break;
            }
            s.push_back(s[idx] + t[idx] + s[idx]);
        }

        int a = s.size() - 1;

        h.resize(n + 1);
        h[n].resize(26);
        for(int i = n - 1; i >= 0; i--) {
            h[i] = h[i + 1];
            h[i][t[i] - 'a'] = mod.add(h[i][t[i] - 'a'], p2_inv[i]);
        }

        for(const auto &query : queries) {
            string w = query.first;
            int k = query.second;

            int ans = mod.mul(p2[k], count_occurrences(s[0], w));

            for(int j = 0; j < a && j < k; j++) {
                ans = mod.add(ans, mod.mul(p2[k - 1 - j], get_g(w, j)));
            }

            vector<int> prefix, suffix;
            tie(prefix, suffix) = get_pre_suf(w, a);

            if(a < k) {
                int l = w.size();
                for(int x = 0; x < l; x++) {
                    int cur = prefix[x] * suffix[l - x - 1];
                    if(cur == 0) {
                        continue;
                    }
                    ans = mod.add(ans, mod.mul(p2[k - 1], mod.sub(h[a][w[x] - 'a'], h[k][w[x] - 'a'])));
                }
            }

            Io::write(ans);
        }
    }
};

void init() {
    ios::sync_with_stdio(false);

    p2.resize(MAXM);
    p2[0] = 1;
    for(int i = 1; i < p2.size(); i++) {
        p2[i] = mod.mul(p2[i - 1], 2);
    }

    p2_inv.resize(MAXM);
    p2_inv[MAXM - 1] = mod.inv(p2[MAXM - 1]);
    for(int i = MAXM - 2; i >= 0; i--) {
        p2_inv[i] = mod.mul(p2_inv[i + 1], 2);
    }
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
