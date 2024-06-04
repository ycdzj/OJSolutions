#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN = 2e5 + 5;

int n;
long long p[MAXN], x, a, y, b, k;

long long get(int cnt_a, int cnt_b, int cnt_ab) {
    pair<long long, int> pr[3]{ {x, cnt_a}, {y, cnt_b}, {x + y, cnt_ab} };
    sort(pr, pr + 3);
    long long res = 0;
    int cur = n;
    for(int i = 2; i >= 0; i--) {
        res += (p[cur - pr[i].second] - p[cur]) / 100 * pr[i].first;
        cur -= pr[i].second;
    }
    return res;
}

int main() {
    int q;
    scanf("%d", &q);
    while(q--) {
        scanf("%d", &n);
        for(int i = 0; i < n; i++) {
            scanf("%lld", &p[i]);
        }
        scanf("%lld%lld%lld%lld%lld", &x, &a, &y, &b, &k);
        sort(p, p + n);
        p[n] = 0;
        for(int i = n - 1; i >= 0; i--) {
            p[i] += p[i + 1];
        }
        int ans = -1;
        for(int i = 0, cnt_a = 0, cnt_b = 0, cnt_ab = 0; i < n; i++) {
            if((i + 1) % a == 0 && (i + 1) % b == 0) {
                cnt_ab++;
            }
            else if((i + 1) % a == 0) {
                cnt_a++;
            }
            else if((i + 1) % b == 0) {
                cnt_b++;
            }
            if(get(cnt_a, cnt_b, cnt_ab) >= k) {
                ans = i + 1;
                break;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
