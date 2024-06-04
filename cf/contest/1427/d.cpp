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
    static void read(char* val) { scanf("%s", val); }
    static void read(string &val) {
        const int BUFFER_SIZE = 1e5 + 5;
        static char buffer[BUFFER_SIZE];
        scanf("%s", buffer);
        val = buffer;
    }
    static void read_n(vector<int> &val, int n) {
        val.resize(n);
        for(int i = 0; i < n; i++) {
            scanf("%d", &val[i]);
        }
    }
    
    static void write(int val) { printf("%d\n", val); }
    static void write(const char* val) { printf("%s\n", val); }
    static void write(const string &val) { printf("%s\n", val.c_str()); }
    static void write(const vector<int> &val) {
        for(int i = 0; i < val.size(); i++) {
            if(i > 0) {
                putchar(' ');
            }
            printf("%d", val[i]);
        }
        putchar('\n');
    }
};

// ----------------------Template End----------------------

class Solver {
    int n;
    vector<int> a;

    void flip(const vector<int> &ans) {
        vector<int> new_a(a.size());
        for(int i = 0, sum = 0; i < ans.size(); i++) {
            copy(a.begin() + sum, a.begin() + sum + ans[i], new_a.end() - sum - ans[i]);
            sum += ans[i];
        }
        a = new_a;
    }
public:
    void read() {
        IO::read(n);
        IO::read_n(a, n);
    }
    void solve() {
        if(!(n & 1)) {
            for(int &val : a) {
                val = n + 1 - val;
            }
        }
        vector<vector<int>> ans_list;
        for(int i = 0; i < n; i++) {
            vector<int> ans;
            if(!(i & 1)) {
                int max_pos = max_element(a.begin() + i, a.end()) - a.begin();
                ans.insert(ans.end(), i, 1);
                ans.push_back(max_pos - i + 1);
                if(n - max_pos - 1 > 0) {
                    ans.push_back(n - max_pos - 1);
                }
            } else {
                int max_pos = max_element(a.begin(), a.end() - i) - a.begin();
                if(max_pos > 0) {
                    ans.push_back(max_pos);
                }
                ans.push_back(n - i - max_pos);
                ans.insert(ans.end(), i, 1);
            }
            if(ans.size() > 1) {
                ans_list.push_back(ans);
                flip(ans);
            }
        }
        IO::write(ans_list.size());
        for(int i = 0; i < ans_list.size(); i++) {
            IO::write(ans_list[i].size());
            IO::write(ans_list[i]);
        }
    }
};

void init() {
    ios::sync_with_stdio(false);
}

int main() {
    init();

    int t = 1;
    //IO::read(t);

    while(t--) {
        Solver solver;
        solver.read();
        solver.solve();
    }
    return 0;
}
