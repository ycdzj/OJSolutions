#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const long long WHOLE = 360 * 12 * (long long)1e10;
const long long NS = 1e9;
const long long S = 60;
const long long M = 60;

long long addmod(long long a, long long b) {
    return (a + b) % WHOLE;
}
long long mulmod(long long a, long long b) {
    return (a * b) % WHOLE;
}
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

long long  solve(int i_case) {
    vector<long long> a(3);
    for(int i = 0; i < 3; i++) {
        cin >> a[i];
    }
    sort(a.begin(), a.end());
    do {
        long long x11 = addmod(a[1], WHOLE - a[0]);
        long long x719 = addmod(a[2], WHOLE - a[0]);
        long long x = addmod(mulmod(x719, 3), WHOLE - mulmod(x11, 196));
        if(mulmod(x, 11) == x11 && mulmod(x, 719) == x719) {
            return x;
        }
    } while (next_permutation(a.begin(), a.end()));
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    int t;
    cin >> t;
    for(int i_case = 1; i_case <= t; i_case++) {
        long long h = solve(i_case);
        long long ret_ns = h % NS;
        h /= NS;
        long long ret_s = h % S;
        h /= S;
        long long ret_m = h % M;
        h /= M;
        long long ret_h = h;
        cout << "Case #" << i_case << ": " << ret_h << " " << ret_m << " " << ret_s << " " << ret_ns << endl;
    }
    return 0;
}