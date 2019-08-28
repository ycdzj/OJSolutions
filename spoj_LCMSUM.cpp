#include <cstdio>
#include <vector>
using namespace std;

const int MAXN = 1e6 + 6;

bool vis[MAXN];
int phi[MAXN];
vector<int> primes;
long long f[MAXN];

void calc_prime() {
    phi[1] = 1;
    for(int i = 2; i < MAXN; i++) {
        if(!vis[i]) {
            primes.push_back(i);
            phi[i] = i - 1;
        }
        for(int p : primes) {
            if((long long)i * p >= MAXN) {
                break;
            }
            vis[i * p] = true;
            if(i % p != 0) {
                phi[i * p] = phi[i] * phi[p];
            }
            else {
                phi[i * p] = p * phi[i];
                break;
            }
        }
    }
}
int main() {
    calc_prime();
    for(int d = 1; d < MAXN; d++) {
        for(int i = d; i < MAXN; i += d) {
            f[i] += (long long)d * phi[d];
        }
    }
    int T;
    scanf("%d", &T);
    while(T--) {
        int n;
        scanf("%d", &n);
        printf("%lld\n", n * (f[n] + 1) / 2);
    }
    return 0;
}
