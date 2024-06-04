#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN = 1e5 + 5;

int n;
long long k;
int a[MAXN];

int main() {
    scanf("%d%lld", &n, &k);
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    sort(a, a + n);
    long long min_val = a[0], max_val = a[n - 1];
    int l = 0, r = n - 1;
    while(min_val < max_val) {
        while(l + 1 < n && a[l + 1] == min_val) {
            l++;
        }
        while(r - 1 >= 0 && a[r - 1] == max_val) {
            r--;
        }
        //a[0, l] == min_val
        //a[r, n) == max_val
        if(l + 1 < n - r) {
            long long cnt = min(k / (l + 1), a[l + 1] - min_val);
            cnt = min(cnt, max_val - min_val);
            if(cnt == 0) {
                break;
            }
            k -= cnt * (l + 1);
            min_val += cnt;
        }
        else {
            long long cnt = min(k / (n - r), max_val - a[r - 1]);
            cnt = min(cnt, max_val - min_val);
            if(cnt == 0) {
                break;
            }
            k -= cnt * (n - r);
            max_val -= cnt;
        }
    }
    printf("%lld\n", max_val - min_val);
    return 0;
}
