#include <cstdio>
#include <vector>
using namespace std;

const int MAXN = 1e6 + 6;

bool vis[MAXN];
int mob[MAXN], f[MAXN];
vector<int> primes;

void prime() {
    mob[1] = 1;
    f[1] = 1;
    for(int i = 2; i < MAXN; i++) {
        if(!vis[i]) {
            primes.push_back(i);
            mob[i] = -1;
            f[i] = -2;
        }
        for(int p : primes) {
            if((long long)p * i >= MAXN) {
                break;
            }
            vis[p * i] = true;
            if(i % p == 0) {
                mob[i * p] = 0;
                if((i / p) % p == 0) {
                    f[i * p] = 0;
                }
                else {
                    f[i * p] = f[i / p];
                }
                break;
            }
            else {
                mob[i * p] = -mob[i];
                f[i * p] = f[i] * f[p];
            }
        }
    }
}

int main() {
    prime();
    int T;
    scanf("%d", &T);
    while(T--) {
        int n, m;
        scanf("%d%d", &n, &m);
        long long ans = 0;
        for(int d = 1; d <= n && d <= m; d++) {
            long long cur_n = 0;
            for(int i = d; i <= n; i += d) {
                cur_n += mob[i];
            }
            long long cur_m = 0;
            for(int i = d; i <= m; i+= d) {
                cur_m += mob[i];
            }
            ans += f[d] * cur_n * cur_m;
        }
        printf("%lld\n", ans);
    }
    return 0;
}
