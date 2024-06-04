#include <cstdio>
typedef long long ll;
ll f(int i, int j) {
    ll cur = 1;
    for(int k = 0; k < j; k++) cur *= i - k;
    for(int k = 2; k <= j; k++) cur /= k;
    for(int k = 0; k < j; k++) cur *= 9;
    return cur;
}
int stk[20];
ll solve(ll x) {
    int top = -1;
    for(ll y = x; y; y /= 10) stk[++top] = y % 10;
    ll ans = 0;
    for(int i = top, cnt = 0; i >= 0; i--) {
        if(stk[i] > 0) {
            for(int k = 0; k <= 3 - cnt - 1; k++) ans += f(i, k) * (stk[i] - 1);
            for(int k = 0; k <= 3 - cnt; k++) ans += f(i, k);
            if(++cnt > 3) break;
        }
    }
    return ans;
}
int main() {
    int T; scanf("%d", &T);
    while(T--) {
        ll l, r; scanf("%lld%lld", &l, &r);
        printf("%lld\n", solve(r + 1) - solve(l));
    }
    return 0;
}