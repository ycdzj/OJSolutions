#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAXN = 2e5 + 5;

char str[MAXN];

int l, r, val;

void check() {
    if(l > r) {
        r = l;
        val = 0;
    }
}

void r_right() {
    val <<= 1;
    if(str[r++] == '1') {
        val++;
    }
}

void r_left() {
    val >>= 1;
    r--;
    check();
}
void l_right() {
    if(str[l] == '1') {
        val -= (1 << (r - l - 1));
    }
    l++;
    check();
}

int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        scanf("%s", str);
        int len = strlen(str);
        l = 0;
        r = 0;
        val = 0;
        int ans = 0;
        while(l < len) {
            while(r - l > 0 && r - l <= val) {
                r_left();
            }
            while(r <= len && r - l >= val) {
                if(r - l == val && val != 0) {
                    ans++;
                }
                r_right();
            }
            l_right();
        }
        printf("%d\n", ans);
    }
    return 0;
}
