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

int ans;
long long ans_num;
long long n;

void dfs(int idx, int cnt, long long val) {
    if(val > n) {
        return;
    }
    if(ans < cnt) {
        ans = cnt;
        ans_num = val;
    }
    else if(ans == cnt) {
        ans_num = min(ans_num, val);
    }

    int p = 1;
    val *= primes[idx];

    while(val <= n) {
        dfs(idx + 1, cnt * (p + 1), val);
        p++;
        val *= primes[idx];
    }
}
//1 2 3 4 6 12


int main() {
    freopen("divisors.in", "r", stdin);
    freopen("divisors.out", "w", stdout);
    calc_prime();
    while(scanf("%lld", &n) != EOF) {
        ans = -1;
        dfs(0, 1, 1);
        printf("%lld\n", ans_num);
    }
    return 0;
}
