#include <cstdio>
#include <cstring>
#include <algorithm>

const int MOD = 998244353;
inline int addmod(int a, int b) { return (a + b) % MOD; }
inline int mulmod(long long a, int b) { return (a * b) % MOD; }
const int MAXN = 2e5 + 5;
int len;
char str[MAXN];
int main() {
    scanf("%d%s", &len, str);
    int sum = 0;
    for(int i = 1; i <= len - 1; i++) sum = addmod(sum, i);
    int ans = 0;
    for(char cur = 'a'; cur <= 'z'; cur++) {
        int l = len, r = -1;
        for(int i = 0; i < len; i++) if(str[i] != cur) {
            l = std::min(l, i);
            r = std::max(r, i);
        }
        if(r == -1) {
            ans = addmod(ans, sum);
        }
        else {
            ans = addmod(ans, mulmod(l + 1, len - r));
        }
    }
    printf("%d\n", addmod(ans, MOD - 25));
    return 0;
}
