#include <cstdio>
#include <unordered_set>
#include <map>
using namespace std;
const int INF = 1e9;
int a[2005];
int main() {
    int n;
    scanf("%d", &n);
    map<int, int> cnt;
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        cnt[a[i]]++;
    }
    int cnt_same = 0;
    for(auto pr : cnt) {
        if(pr.second > 1) {
            cnt_same++;
        }
    }
    int ans = INF;
    if(cnt_same == 0) {
        ans = 0;
    }
    for(int l = 0; l < n; l++) {
        map<int, int> cur(cnt);
        int cur_same = cnt_same;
        for(int r = l; r < n; r++) {
            if(--cur[a[r]] == 1) {
                --cur_same;
            }
            if(cur_same == 0) {
                ans = min(ans, r - l + 1);
            }
        }
    }
    if(ans == INF) {
        ans = 0;
    }
    printf("%d\n", ans);
    return 0;
}
