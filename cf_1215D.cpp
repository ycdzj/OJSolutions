#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN = 2e5 + 5;

int n;
char str[MAXN];

bool solve(int cnt, int val) {
    val -= 9 * (cnt - 1);
    for(int y = 0; y <= 9; y++) {
        if(y + 9 < val || y > val) {
            return false;
        }
    }
    return true;
}

int main() {
    scanf("%d", &n);
    scanf("%s", str);
    int pre_l = 0, pre_r = 0, cnt_l = 0, cnt_r = 0;
    for(int i = 0; i < n / 2; i++) {
        if(str[i] == '?') {
            cnt_l++;
        }
        else {
            pre_l += str[i] - '0';
        }
    }
    for(int i = n / 2; i < n; i++) {
        if(str[i] == '?') {
            cnt_r++;
        }
        else {
            pre_r += str[i] - '0';
        }
    }
    int d = min(cnt_l, cnt_r);
    cnt_l -= d;
    cnt_r -= d;
    int val = pre_r - pre_l;
    bool ans;
    if(cnt_l == 0 && cnt_r == 0) {
        ans = (val == 0);
    }
    else if(cnt_l != 0) {
        ans = solve(cnt_l / 2, val);
    }
    else {
        ans = solve(cnt_r / 2, -val);
    }
    if(ans) {
        printf("Bicarp\n");
    }
    else {
        printf("Monocarp\n");
    }
    return 0;
}
