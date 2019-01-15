#include <cstdio>
const int MAXN = 1e5 + 5;
int n, m;
int cnt[MAXN];
int rcnt[MAXN];
int main() {
    scanf("%d%d", &n, &m);
    rcnt[0] = n;
    for(int i = 0; i < m; i++) {
        int a; scanf("%d", &a);
        rcnt[cnt[a]]--;
        cnt[a]++;
        rcnt[cnt[a]]++;
        if(rcnt[0] == 0) {
            putchar('1');
            for(int i = 1; i <= n; i++) {
                rcnt[cnt[i]]--;
                cnt[i]--;
                rcnt[cnt[i]]++;
            }
        }
        else {
            putchar('0');
        }
    }
    return 0;
}