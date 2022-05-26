#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

void solve() {
    int n;
    scanf("%d", &n);

    vector<long long> d(n);
    for(int i = 0; i < n; i++) {
        scanf("%lld", &d[i]);
    }

    sort(d.begin(), d.end());

    vector<long long> presum_d(d);
    for(int i = 1; i < n; i++) {
        presum_d[i] += presum_d[i - 1];
    }

    long long ans = 0;
    for(int i = 1; i < n; i++) {
        ans -= d[i] * i;
        ans += presum_d[i - 1];
    }

    ans += d[n - 1];

    printf("%lld\n", ans);
}

int main() {
    int t;
    scanf("%d", &t);
    while(t--) {
        solve();
    }
    return 0;
}

