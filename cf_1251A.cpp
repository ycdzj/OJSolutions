#include <cstdio>
#include <cstring>

char str[100005];
bool vis[26];

void update(int ch, int cnt) {
    if(ch == -1) {
        return;
    }
    if(cnt & 1) {
        vis[ch] = true;
    }
}

int main() {
    int t;
    scanf("%d", &t);
    while(t--) {
        scanf("%s", str);
        for(int i = 0; i < 26; i++) {
            vis[i] = false;
        }
        for(int i = 0, pre_char = -1, pre_cnt = 0; true; i++) {
            if(str[i] == '\0' || str[i] - 'a' != pre_char) {
                update(pre_char, pre_cnt);
                pre_char = str[i] - 'a';
                pre_cnt = 1;
            }
            else {
                pre_cnt++;
            }
            if(str[i] == '\0') {
                break;
            }
        }
        for(int i = 0; i < 26; i++) {
            if(vis[i]) {
                putchar('a' + i);
            }
        }
        putchar('\n');
    }
    return 0;
}
