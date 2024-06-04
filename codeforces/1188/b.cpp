#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

inline int addmod(int a, int b, int mod) {
    return (a + b) % mod;
}
inline int mulmod(long long a, int b, int mod) {
    return (a * b) % mod;
}

int main() {
    int n, p, k;
    cin >> n >> p >> k;
    unordered_map<int, int> cnt;
    for(int i = 0; i < n; i++) {
        int a;
        cin >> a;
        int a4 = mulmod(a, a, p);
        a4 = mulmod(a4, a4, p);
        int ak = mulmod(a, k, p);
        int val = addmod(a4, p - ak, p);
        cnt[val]++;
    }
    long long ans = 0;
    for(auto pr : cnt) {
        ans += (long long)pr.second * (pr.second - 1);
    }
    cout << ans / 2 << endl;
    return 0;
}
