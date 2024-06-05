#include <cstdio>
#include <algorithm>
long long solve1(long long n) {
    long long ans = 0;
    long long pre = 0;
    for(long long i = 1; n; i *= 10) {
        int cur = n % 10;
        if(cur & 1) {
            ans += i - pre;
            pre = 0;
            n++;
        }
        pre += i * (n % 10);
        n /= 10;
    }
    return ans;
}
long long solve2(long long n) {
    int digit[20], cnt = 0;
    for(long long cur = n; cur != 0; cur /= 10) {
        digit[cnt++] = cur % 10;
    }
    for(int i = cnt - 1; i >= 0; i--) {
        if(digit[i] & 1) {
            digit[i]--;
            for(int j = i - 1; j >= 0; j--) digit[j] = 8;
            break;
        }
    }
    long long m = 0;
    for(int i = cnt - 1; i >= 0; i--) {
        m = m * 10 + digit[i];
    }
    return n - m;
}
int main() {
    int T; scanf("%d", &T);
    for(int cnt_case = 1; cnt_case <= T; cnt_case++) {
        long long n; scanf("%lld", &n);
        printf("Case #%d: %lld\n", cnt_case, std::min(solve1(n), solve2(n)));
    }
    return 0;
}
