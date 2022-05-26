#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>
#include <map>
#include <unordered_map>
using namespace std;

long long query(long long l, long long r) {
    cout << "? " << l << ' ' << r << endl;
    cout.flush();

    long long res;
    cin >> res;

    if(res == -1) {
        exit(0);
    }

    return res;
}

class Solver {
    long long n;

    long long find_i() {
        long long l = 1, r = n;
        while(l < r) {
            long long mid = l + (r - l) / 2 + 1;
            if(query(1, mid) == 0) {
                l = mid;
            } else {
                r = mid - 1;
            }
        }
        return l;
    }

public:
    void read() {
        cin >> n;
    }

    void solve() {
        long long i = find_i();
        long long q_i_k = query(i, n);
        long long q_i1_k = query(i + 1, n);
        long long j = q_i_k - q_i1_k + 1 + i;
        long long x = j - i;
        long long cy2 = q_i_k - x * (x - 1) / 2;
        long long y = (1 + (long long)(sqrt(1 + 8 * cy2) + 0.5)) / 2;
        long long k = y + j - 1;

        cout << "! " << i << ' ' << j << ' ' << k << endl;
    }
};

int main() {
    ios::sync_with_stdio(false);
    int t = 1;
    cin >> t;
    while(t--) {
        Solver solver;
        solver.read();
        solver.solve();
    }
    return 0;
}