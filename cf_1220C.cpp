#include <cstdio>

const int MAXN = 5e5 + 5;

char str[MAXN];
bool vis[26];

int main() {
    scanf("%s", str);
    for(int i = 0; str[i] != '\0'; i++) {
        int val = str[i] - 'a';
        bool flag = false;
        for(int j = 0; j < val; j++) {
            if(vis[j]) {
                flag = true;
            }
        }
        if(flag) {
            printf("Ann\n");
        }
        else {
            printf("Mike\n");
        }
        vis[val] = true;
    }
    return 0;
}
