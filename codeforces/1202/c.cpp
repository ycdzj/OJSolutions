#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 2e5 + 5;
const long long INF = 1e18;

char seq[MAXN];
int len;
struct Rect {
    int x, y;
    int min_x, max_x, min_y, max_y;
} prefix[MAXN];

void calc_prefix() {
    int x = 0, y = 0, min_x = 0, max_x = 0, min_y = 0, max_y = 0;
    for(int i = 1; i <= len; i++) {
        if(seq[i] == 'W') {
            y++;
        }
        else if(seq[i] == 'A') {
            x--;
        }
        else if(seq[i] == 'S') {
            y--;
        }
        else if(seq[i] == 'D') {
            x++;
        }
        min_x = min(min_x, x);
        max_x = max(max_x, x);
        min_y = min(min_y, y);
        max_y = max(max_y, y);
        prefix[i] = {x, y, min_x, max_x, min_y, max_y};
    }
}

void change(char c, Rect &rect) {
    if(c == 'W') {
        rect.y++;
        rect.max_y++;
        rect.min_y++;
    }
    else if(c == 'A') {
        rect.x--;
        rect.max_x--;
        rect.min_x--;
    }
    else if(c == 'S') {
        rect.y--;
        rect.max_y--;
        rect.min_y--;
    }
    else if(c == 'D') {
        rect.x++;
        rect.max_x++;
        rect.min_x++;
    }
    rect.max_x = max(rect.max_x, 0);
    rect.min_x = min(rect.min_x, 0);
    rect.max_y = max(rect.max_y, 0);
    rect.min_y = min(rect.min_y, 0);
}
const char dir[4] = {'W', 'A', 'S', 'D'};
int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        scanf("%s", seq + 1);
        len = strlen(seq + 1);
        calc_prefix();
        Rect cur = {0, 0, 0, 0, 0, 0};
        long long ans = (long long)(prefix[len].max_x - prefix[len].min_x + 1) * (prefix[len].max_y - prefix[len].min_y + 1);
        for(int i = len; i >= 1; i--) {
            change(seq[i], cur);
            for(int j = 0; j < 4; j++) {
                Rect nxt = cur;
                change(dir[j], nxt);
                long long max_x = max(prefix[i - 1].max_x, prefix[i - 1].x + nxt.max_x);
                long long min_x = min(prefix[i - 1].min_x, prefix[i - 1].x + nxt.min_x);
                long long max_y = max(prefix[i - 1].max_y, prefix[i - 1].y + nxt.max_y);
                long long min_y = min(prefix[i - 1].min_y, prefix[i - 1].y + nxt.min_y);
                ans = min(ans, (max_x - min_x + 1) * (max_y - min_y + 1));
            }
        }
        printf("%lld\n", ans);
    }
    return 0;
}
