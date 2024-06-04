#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n;
    scanf("%d", &n);
    vector<pair<long long, int>> v(n);
    vector<bool> vis(n, false);
    for(int i = 0; i < n; i++) {
        scanf("%lld", &v[i].first);
    }
    for(int i = 0; i < n; i++) {
        scanf("%d", &v[i].second);
    }
    sort(v.begin(), v.end());
    for(int i = 0; i < n; ) {
        int j = i;
        while(j < n && v[j].first == v[i].first) {
            j++;
        }
        int cnt = j - i;
        if(cnt > 1) {
            for(int k = 0; k < i; k++) {
                if((v[k].first & v[i].first) == v[k].first) {
                    vis[k] = true;
                }
            }
            for(int k = i; k < j; k++) {
                vis[k] = true;
            }
        }
        i = j;
    }
    long long ans = 0;
    for(int i = 0; i < n; i++) {
        if(vis[i]) {
            ans += v[i].second;
        }
    }
    printf("%lld\n", ans);
    return 0;
}