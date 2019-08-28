#include <cstdio>
#include <vector>
using namespace std;

const int MAXN = 1e5 + 5;

vector<int> primes;
bool vis[MAXN];

void calc_prime() {
    for(int i = 2; i < MAXN; i++) {
        if(!vis[i]) {
            primes.push_back(i);
        }
        for(int p : primes) {
            if((long long)i * p >= MAXN) {
                break;
            }
            vis[i * p] = true;
            if(i % p == 0) {
                break;
            }
        }
    }
}

int n;
long long ans;

void dfs(int idx, int cnt, long long val) {
    if(val >= ans || n % cnt != 0) {
        return;
    }
    if(cnt == n) {
        ans = val;
    }
    else {
        long long nxt_val = val * primes[idx];
        int nxt_cnt = 1;
        while(nxt_val < ans) {
            dfs(idx + 1, cnt * (1 + nxt_cnt), nxt_val);
            nxt_val *= primes[idx];
            nxt_cnt++;
        }
    }
}

int main() {
    calc_prime();
    scanf("%d", &n);
    ans = 1e18;
    dfs(0, 1, 1);
    printf("%lld\n", ans);
    return 0;
}
