#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 2e5 + 5;

int n, m, a[MAXN];
int buf[MAXN * 2];
int ans_l[MAXN], ans_r[MAXN];

void shift_right(int *&p) {
    if(p[n] == n) {
        return;
    }
    p[n - 1] += p[n];
    p[n] = 0;
    p--;
}
void shift_left(int *&p) {
    if(p[1] == n) {
        return;
    }
    p[2] += p[1];
    p[1] = 0;
    p++;
}
void init(int *&p) {
    p = buf + MAXN;
    memset(buf, 0, sizeof(buf));
    fill(p + 1, p + 1 + n, 1);
}

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= m; i++) {
        scanf("%d", &a[i]);
    }
    if(n == 1) {
        printf("0\n");
    }
    else {
        int *p;
        init(p);
        for(int i = 1; i <= m; i++) {
            shift_right(p);
            p[a[i] - 1] += p[a[i]];
            p[a[i]] = 0;
        }
        shift_right(p);
        for(int i = n, cur = n; i >= 1; i--) {
            while(p[i] > 0) {
                ans_r[cur--] = i;
                p[i]--;
            }
        }

        init(p);
        for(int i = 1; i <= m; i++) {
            shift_left(p);
            p[a[i] + 1] += p[a[i]];
            p[a[i]] = 0;
        }
        shift_left(p);
        for(int i = 1, cur = 1; i <= n; i++) {
            while(p[i] > 0) {
                ans_l[cur++] = i;
                p[i]--;
            }
        }
        long long ans = 0;
        for(int i = 1; i <= n; i++) {
            ans += ans_r[i] - ans_l[i] + 1;
        }
        printf("%lld\n", ans);
    }

    return 0;
}
