#include <cstdio>

char str[100005];

int main() {
    int l;
    scanf("%d%s", &l, str);
    int cnt_0 = 0, cnt_1 = 0;
    for(int i = 0; i < l; i++) {
        if(str[i] == 'n') {
            cnt_1++;
        }
        else if(str[i] == 'z') {
            cnt_0++;
        }
    }
    while(cnt_1--) {
        printf("1 ");
    }
    while(cnt_0--) {
        printf("0 ");
    }
    printf("\n");
    return 0;
}
