#include <cstdio>
#include <algorithm>
#include <map>
using namespace std;

const int MAXN = 1e5 + 5;

int pri[MAXN];
void init() {
    for(int i = 0; i < MAXN; i++) {
        pri[i] = i;
    }
    for(int i = 2; i < MAXN; i++) {
        if(pri[i] == i) {
            for(int j = i + i; j < MAXN; j += i) {
                pri[j] = min(pri[j], i);
            }
        }
    }
}

void my_pow(long long &val, int a, int x) {
    if(val == -1) {
        return;
    }
    while(x--) {
        val *= a;
        if(val > MAXN) {
            val = -1;
            return;
        }
    }
}

void calc(long long a, long long &b, long long &c, int k) {
    b = 1;
    c = 1;

    long long pre_val = 1, pre_cnt = 1;
    while(a != 1) {
        if(pri[a] == pre_val) {
            pre_cnt++;
        }
        else {
            my_pow(b, pre_val, pre_cnt % k);
            my_pow(c, pre_val, (k - pre_cnt % k) % k);

            pre_val = pri[a];
            pre_cnt = 1;
        }
        a /= pri[a];
    }
    my_pow(b, pre_val, pre_cnt % k);
    my_pow(c, pre_val, (k - pre_cnt % k) % k);
}
int n, k, a[MAXN];

int main() {
    init();
    scanf("%d%d", &n, &k);
    map<int, int> cnt;
    long long ans = 0;
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        long long b, c;
        calc(a[i], b, c, k);
        if(c != -1) {
            ans += cnt[c];
        }
        cnt[b]++;
    }
    printf("%lld\n", ans);
    return 0;
}
