#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solver {
public:
    void input() {
        cin >> n;
        a.resize(n);
        for(int i = 0; i < n; i++) {
            cin >> a[i];
        }
    }
    void print() {
        cout << solve() << endl;
    }
private:
    vector<int> a;
    int n;
    long long f(int x) {
        long long ans = 0;
        for(int i = 0; i < n; i++) {
            int j = lower_bound(a.begin(), a.end(), x - a[i]) - a.begin();
            if(i < j) {
                ans += j - i - 1;
            } else {
                break;
            }
        }
        return ans;
    }
    int solve() {
        int ans = 0;
        for(int i = 30; i >= 0; i--) {
            for(int j = 0; j < n; j++) {
                a[j] = (a[j] & ((1 << (i + 1)) - 1));
            }
            sort(a.begin(), a.end());

            long long cur = f(1 << (i + 1)) - f(1 << i);
            cur += f(1 << (i + 2)) - f((1 << i) + (1 << (i + 1)));
            if(cur & 1) {
                ans = (ans | (1 << i));
            }
        }
        return ans;
    }
};

int main() {
    ios::sync_with_stdio(false);
    Solver solver;
    solver.input();
    solver.print();
    return 0;
}
