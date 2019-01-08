#include <iostream>
#include <vector>
using namespace std;
const int MAXN = 1e5 + 5;
typedef long long ll;
const ll INF = 1e18;
int p[MAXN];
ll a[MAXN], s[MAXN];
int n;
int main() {
    cin >> n;
    for(int i = 2; i <= n; i++) cin >> p[i];
    for(int i = 1; i <= n; i++) {
        cin >> s[i];
        if(s[i] == -1) a[i] = INF;
    }
    for(int i = 2; i <= n; i++) if(s[i] != -1) {
        a[p[i]] = min(a[p[i]], s[i]);
    }
    for(int i = 1; i <= n; i++) if(s[i] == -1) {
        if(a[i] == INF) continue;
        a[i] -= s[p[i]];
    }
    ll ans = s[1];
    for(int i = 2; i <= n; i++) {
        if(s[i] == -1) {
            if(a[i] == INF) continue;
            if(a[i] < 0) {
                ans = -1;
                break;
            }
            ans += a[i];
        }
        else {
            ans += s[i] - s[p[p[i]]] - a[p[i]];
        }
    }
    cout << ans << endl;
    return 0;
}