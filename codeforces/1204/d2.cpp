#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 1e5 + 5;
const int INF = 1e9;

bool vis[MAXN];
int cnt[MAXN];
char str[MAXN];
int len;

int main() {
    scanf("%s", str + 1);
    len = strlen(str + 1);
    for(int i = 1; i <= len; i++) {
        if(str[i] == '0') {
            cnt[i] = cnt[i - 1] + 1;
        }
        else {
            cnt[i] = cnt[i - 1] - 1;
        }
    }
    int cur_max = -INF;
    for(int i = len; i >= 1; i--) {
        cur_max = max(cur_max, cnt[i]);
        if(cur_max > cnt[i - 1]) {
            vis[i] = true;
        }
    }
    for(int i = 1; i <= len; i++) {
        if(str[i] == '0' || i == len || !vis[i + 1]) {
            printf("0");
        }
        else {
            printf("1");
        }
    }
    printf("\n");
    return 0;
}
