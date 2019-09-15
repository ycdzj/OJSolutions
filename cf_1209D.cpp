#include <cstdio>

const int MAXN = 1e5 + 5;

int f[MAXN];
int find(int x) {
    if(x != f[x]) {
        f[x] = find(f[x]);
    }
    return f[x];
}

int n, k;
int cnt[MAXN];

int main() {
    scanf("%d%d", &n, &k);
    for(int i = 1; i <= n; i++) {
        f[i] = i;
    }
    for(int i = 0; i < k; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        x = find(x);
        y = find(y);
        if(x != y) {
            f[x] = y;
        }
    }
    for(int i = 1; i <= n; i++) {
        cnt[find(i)]++;
    }
    int ans = 0;
    for(int i = 1; i <= n; i++) {
        if(cnt[i] >= 2) {
            ans += cnt[i] - 1;
        }
    }
    printf("%d\n", k - ans);
    return 0;
}
