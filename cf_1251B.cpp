#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXN = 1e5 + 5;

void subtract(int &a, int &b) {
    int val = min(a / 2, b / 2);
    a -= val * 2;
    b -= val * 2;
}

int n, a[MAXN];
char str[MAXN];

int main() {
    int q;
    scanf("%d", &q);
    while(q--) {
        scanf("%d", &n);
        int cnt[2] = {0, 0};
        for(int i = 0; i < n; i++) {
            scanf("%s", str);
            a[i] = strlen(str);
            for(int j = 0; j < a[i]; j++) {
                cnt[str[j] - '0']++;
            }
        }
        int ans = 0;
        for(int i = 0; i < n; i++) {
            a[i] = (a[i] & (~1));
            subtract(a[i], cnt[0]);
            subtract(a[i], cnt[1]);
            if(a[i] == 0) {
                ans++;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
