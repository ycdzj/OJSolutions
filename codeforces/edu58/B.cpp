#include <cstdio>
#include <cstring>
const int MAXN = 5e5 + 5;
char str[MAXN];
int len;
int main() {
    scanf("%s", str);
    len = strlen(str);
    int l = 0, cur = 0;
    while(l < len && cur < 2) {
        if(cur == 0) {
            if(str[l] == '[') cur++;
        }
        else if(cur == 1) {
            if(str[l] == ':') cur++;
        }
        l++;
    }
    int r = len - 1;
    cur = 0;
    while(r >= 0 && cur < 2) {
        if(cur == 0) {
            if(str[r] == ']') cur++;
        }
        else if(cur == 1) {
            if(str[r] == ':') cur++;
        }
        r--;
    }
    if(l <= r + 1) {
        int ans = 0;
        for(int i = l; i <= r; i++) if(str[i] == '|') ans++;
        printf("%d\n", ans + 4);
    }
    else {
        printf("-1\n");
    }
    return 0;
}