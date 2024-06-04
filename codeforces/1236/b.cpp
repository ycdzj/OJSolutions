#include <cstdio>

const int MOD = 1e9 + 7;

int powmod(long long a, int x) {
    long long res = 1;
    while(x) {
        if(x & 1) {
            res = (res * a) % MOD;
        }
        x >>= 1;
        a = (a * a) % MOD;
    }
    return (int)res;
}

int addmod(int a, int b) {
    return (a + b) % MOD;
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    printf("%d\n", powmod(addmod(powmod(2, m), MOD - 1), n));
    return 0;
}
