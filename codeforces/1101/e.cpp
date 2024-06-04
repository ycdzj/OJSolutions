#include <cstdio>
#include <algorithm>
const int MAXN = 5e5 + 5;
int main() {
    int n; scanf("%d", &n);
    int h = 0, w = 0;
    while(n--) {
        char cmd[10]; scanf("%s", cmd);
        if(cmd[0] == '+') {
            int x, y; scanf("%d%d", &x, &y);
            if(x > y) std::swap(x, y);
            h = std::max(h, x);
            w = std::max(w, y);
        }
        else if(cmd[0] == '?') {
            int cur_h, cur_w; scanf("%d%d", &cur_h, &cur_w);
            if(cur_h > cur_w) std::swap(cur_h, cur_w);
            if(cur_h >= h && cur_w >= w) printf("YES\n");
            else printf("NO\n");
        }
    }
    return 0;
}