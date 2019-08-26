#include <cstdio>
#include <map>
using namespace std;

const int MAXN = 2005;
const int INF = 1e9;

int n;
int a[MAXN];

int main() {
    scanf("%d", &n);
    map<int, int> cnt;
    int cnt_same = 0;
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        if(cnt[a[i]]++ == 1) {
            cnt_same++;
        }
    }
    int ans = INF;
    int l = 0, r = 0;
    if(cnt_same == 0) {
        ans = 0;
    }
    while(true) {
        if(cnt_same == 0) {
            if(l == r) {
                break;
            }
            if(cnt[a[l]]++ == 1) {
                cnt_same++;
            }
            l++;
            if(cnt_same == 0) {
                ans = min(ans, r - l);
            }
        }
        else {
            if(r == n) {
                break;
            }
            if(--cnt[a[r]] == 1) {
                cnt_same--;
            }
            r++;
            if(cnt_same == 0) {
                ans = min(ans, r - l);
            }
        }
    }
    printf("%d\n", ans);
    return 0;
}
