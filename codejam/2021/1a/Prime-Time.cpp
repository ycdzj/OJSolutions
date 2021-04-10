#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

struct Item {
    long long p, n;
};

bool vis[123];

void sieve(long long s) {
    long long t = s - 29940;
    for(int p = 2; p <= 499; p++) {
        for(long long i = t + (p - t % p) % p; i <= s; i += p) {
            vis[i] = true;
        }
    }
}

void solve(int i_case) {
    int m;
    scanf("%d", &m);
    vector<Item> items(m);
    long long sum_pn = 0;
    for(int i = 0; i < m; i++) {
        scanf("%lld%lld", &items[i].p, &items[i].n);
        sum_pn += items[i].p * items[i].n;
    }
    long long ans = 0;
    for(int delta = 1; delta <= 65 * 500; delta++) {
        long long s = sum_pn - delta;
        if(s < 1) {
            continue;
        }
        long long sum_second = 0;
        for(int i = 0; i < m; i++) {
            int cnt = 0;
            while(s > 1 && s % items[i].p == 0) {
                s /= items[i].p;
                cnt++;
            }
            if(cnt <= items[i].n) {
                sum_second += items[i].p * cnt;
            } else {
                sum_second = -1;
                break;
            }
        }
        if(sum_second == -1) {
            continue;
        }
        if(s != 1) {
            continue;
        }
        if(sum_second == delta) {
            ans = sum_pn - delta;
            break;
        }
    }
    printf("Case #%d: %lld\n", i_case, ans);
}

int main() {
    int t;
    scanf("%d", &t);
    for(int i = 1; i <= t; i++) {
        solve(i);
    }
    return 0;
}