#include <iostream>
#include <cmath>
using namespace std;
typedef long long ll;
ll n;
int main() {
    cin >> n;
    ll m = sqrt(n);
    ll ans = n * 2;
    for(ll a = m - 5; a <= m + 5; a++) for(ll b = m - 5; b <= m + 5; b++) {
        if(a > 0 && b > 0 && a * b >= n) {
            ans = min(ans, a + b);
        }
    }
    cout << ans << endl;
    return 0;
}