#include <cstdio>
const int MAXN = 2e5 + 5;
char str[MAXN];
int n;
int main() {
    scanf("%d", &n);
    scanf("%s", str);
    for(int i = 0; i + 1 < n; i++) {
        if(str[i] > str[i + 1]) {
            str[i] = '\0';
            printf("%s%s\n", str, str + i + 1);
            return 0;
        }
    }
    str[n - 1] = '\0';
    printf("%s\n", str);
    return 0;
}