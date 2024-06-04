#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;


int main() {
    int n;
    scanf("%d", &n);
    vector<int> v(n);
    vector<bool> vis(n);
    for(int i = 0; i < n; i++) {
        scanf("%d", &v[i]);
    }
    sort(v.begin(), v.end());
    int ans = 0;
    for(int i = 0; i < n; i++) {
        if(!vis[i]) {
            vis[i] = true;
            ans++;
            for(int j = i + 1; j < n; j++) {
                if(v[j] % v[i] == 0) {
                    vis[j] = true;
                }
            }
        }
    }
    printf("%d\n", ans);
    return 0;
}
