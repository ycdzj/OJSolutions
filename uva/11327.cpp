#include <cstdio>
#include <vector>
using namespace std;

const int MAXN = 3e5 + 5;

bool vis[MAXN];
vector<int> primes;
int phi[MAXN];

int gcd(int a, int b) {
    if(b == 0) {
        return a;
    }
    return gcd(b, a % b);
}
void calc_prime() {
    phi[1] = 2;
    for(int i = 2; i < MAXN; i++) {
        if(!vis[i]) {
            primes.push_back(i);
            phi[i] = i - 1;
        }
        for(int p : primes) {
            if((long long)p * i >= MAXN) {
                break;
            }
            vis[p * i] = true;
            if(i % p != 0) {
                phi[p * i] = phi[p] * phi[i];
            }
            else {
                phi[p * i] = p * phi[i];
                break;
            }
        }
    }
}
int main() {
    calc_prime();
    long long k;
    while(scanf("%lld", &k) != EOF) {
        if(k == 0) {
            break;
        }
        for(int i = 1; i < MAXN; i++) {
            if(k <= phi[i]) {
                for(int j = 0; j <= i; j++) {
                    if(gcd(j, i) == 1) {
                        if(--k == 0) {
                            printf("%d/%d\n", j, i);
                            break;
                        }
                    }
                }
                break;
            }
            else {
                k -= phi[i];
            }
        }
    }
    return 0;
}
