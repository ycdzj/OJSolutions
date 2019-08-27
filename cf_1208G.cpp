#include <cstdio>
#include <algorithm>
#include <numeric>

using namespace std;
const int MAXN = 1e6 + 6;

bool vis[MAXN];
int pri[MAXN], cnt_pri;
int phi[MAXN];

void prime() {
    phi[1] = 1;
    for(int i = 2; i < MAXN; i++) {
        if(!vis[i]) {
            pri[cnt_pri++] = i;
            phi[i] = i - 1;
        }
        for(int j = 0; j < cnt_pri; j++) {
            if((long long)i * pri[j] >= MAXN) {
                break;
            }
            vis[i * pri[j]] = true;
            if(i % pri[j] != 0) {
                phi[i * pri[j]] = phi[i] * phi[pri[j]];
            }
            else {
                phi[i * pri[j]] = pri[j] * phi[i];
                break;
            }
        }
    }
}

int main() {
    prime();
    int n, k;
    scanf("%d%d", &n, &k);
    sort(phi + 3, phi + n + 1);
    long long ans = accumulate(phi + 3, phi + 3 + k, (long long)0);
    if(k == 1) {
        ans--;
    }
    printf("%lld\n", ans + 2);
    return 0;
}
