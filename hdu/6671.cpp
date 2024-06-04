#include <cstdio>
#include <cstring>
#include <vector>
#include <array>
using namespace std;

vector<array<array<long long, 1024>, 2>> f[10], g[10];
int n;
char str[10][1005];
int len[10];

bool check(int x, int l, int rev) {
    if(rev == 0) {
        for(int i = 0; i <= l - 1 - i; i++) {
            if(str[x][i] != str[x][l - 1 - i]) {
                return false;
            }
        }
    }
    else {
        for(int i = 0; i <= l - 1 - i; i++) {
            if(str[x][len[x] - 1 - i] != str[x][len[x] - l + i]) {
                return false;
            }
        }
    }
    return true;
}

inline char get_ch(int i, int r, int idx) {
    if(r == 0) {
        return str[i][idx];
    }
    else {
        return str[i][len[i] - 1 - idx];
    }
}

bool checkl(int i, int j, int r, int x, int rx) {
    for(int k = 0; k < j && k < len[x]; k++) {
        if(get_ch(i, r, len[i] - j + k) != get_ch(x, rx, len[x] - 1 - k)) {
            return false;
        }
    }
    return true;
}

bool checkr(int i, int j, int r, int x, int rx) {
    for(int k = 0; k < j && k < len[x]; k++) {
        if(get_ch(x, rx, k) != get_ch(i, r, j - 1 - k)) {
            return false;
        }
    }
    return true;
}

int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        for(int i = 0; i < n; i++) {
            scanf("%s", str[i]);
            len[i] = strlen(str[i]);
            f[i].assign(len[i] + 1, {});
            g[i].assign(len[i] + 1, {});
            for(int l = 0; l <= len[i]; l++) {
                for(int r = 0; r < 2; r++) {
                    if(check(i, l, r)) {
                        f[i][l][r ^ 1][0] = 1;
                        g[i][l][r][0] = 1;
                    }
                }
            }
        }
        int mask = (1 << n);
        for(int k = 1; k < mask; k++) {
            for(int i = 0; i < n; i++) {
                if(k >> i & 1) {
                    continue;
                }
                for(int j = 0; j <= len[i]; j++) {
                    for(int r = 0; r < 2; r++) {
                        for(int x = 0; x < n; x++) {
                            for(int rx = 0; rx < 2; rx++) {
                                if((k >> x & 1) ) {
                                    if(checkl(i, j, r, x, rx)) {
                                        if(len[x] >= j) {
                                            f[i][j][r][k] += g[x][len[x] - j][rx][k ^ (1 << x)];
                                        }
                                        else {
                                            f[i][j][r][k] += f[i][j - len[x]][r][k ^ (1 << x)];
                                        }
                                    }
                                    if(checkr(i, j, r, x, rx)) {
                                        if(len[x] >= j) {
                                            g[i][j][r][k] += f[x][len[x] - j][rx][k ^ (1 << x)];
                                        }
                                        else {
                                            g[i][j][r][k] += g[i][j - len[x]][r][k ^ (1 << x)];
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        long long ans = 0;
        for(int i = 0; i < n; i++) {
            for(int r = 0; r < 2; r++) {
                for(int k = 0; k < mask; k++) {
                    ans += f[i][len[i]][r][k];
                }
            }
        }
        printf("%lld\n", ans);
    }
    return 0;
}
