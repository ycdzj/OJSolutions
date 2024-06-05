#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN = 1e5 + 5;
const int HIGH = 50;

int n;
long long m, a[MAXN];
long long f[HIGH + 1];
int cnt[HIGH + 1];

int main() {
    int T;
    scanf("%d", &T);
    for(int cnt_case = 1; cnt_case <= T; cnt_case++) {
        scanf("%d%lld", &n, &m);
        for(int i = 0; i < n; i++) {
            scanf("%lld", &a[i]);
        }
        for(int i = HIGH; i >= 0; i--) {
            int cnt_1 = 0;
            for(int j = 0; j < n; j++) {
                if(a[j] >> i & 1) {
                    cnt_1++;
                }
            }
            cnt[i] = cnt_1;
            cnt_1 = min(cnt_1, n - cnt_1);
            f[i] = ((long long)1 << i) * cnt_1;
        }
        bool flag = false;
        for(int i = 1; i <= HIGH; i++) {
            f[i] += f[i - 1];
            if(f[i] > m) {
                flag = true;
                break;
            }
        }
        long long ans;
        if(flag) {
            ans = -1;
        }
        else {
            long long rem = m;
            ans = 0;
            for(int i = HIGH; i >= 0; i--) {
                long long nxt = (i > 0 ? f[i - 1] : 0);
                long long val_1 = ((long long)1 << i) * (n - cnt[i]);
                long long val_0 = ((long long)1 << i) * cnt[i];
                if(val_1 + nxt <= rem) {
                    ans += ((long long)1 << i);
                    rem -= val_1;
                }
                else {
                    rem -= val_0;
                }
            }
        }
        printf("Case #%d: %lld\n", cnt_case, ans);
    }
    return 0;
}
