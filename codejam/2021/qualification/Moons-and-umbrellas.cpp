#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

int x, y;
char str[100005];
int s;

int solve(int lval, int rval, int len) {
    if(lval == '?') {
        return min(solve('J', rval, len), solve('C', rval, len));
    }
    if(rval == '?') {
        return min(solve(lval, 'J', len), solve(lval, 'C', len));
    }
    if(lval == rval) {
        int cnt = (len - 1) / 2;
        return min(0, cnt * (x + y));
    }
    if(lval == 'J' && rval == 'C') {
        int cnt = len / 2 - 1;
        return y + min(0, cnt * (x + y));
    }
    int cnt = len / 2 - 1;
    return x + min(0, cnt * (x + y));
}

int main() {
    int t;
    scanf("%d", &t);
    for(int i_case = 1; i_case <= t; i_case++) {
        scanf("%d%d%s", &x, &y, str);
        s = strlen(str);
        int ans = 0;
        for(int pre = str[0], pre_idx = 0, i = 1; i < s; i++) {
            if(str[i] != '?' || i == s - 1) {
                ans += solve(pre, str[i], i - pre_idx + 1);
                pre = str[i];
                pre_idx = i;
            }
        }
        printf("Case #%d: %d\n", i_case, ans);
    }
    return 0;
}