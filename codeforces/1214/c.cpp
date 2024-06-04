#include <cstdio>
#include <algorithm>
using namespace std;
int n;
char str[200005];
int main() {
    scanf("%d", &n);
    scanf("%s", str);
    int min_ = 0, cnt = 0, cur = 0;
    for(int i = 0; i < n; i++) {
        if(str[i] == ')') {
            cur--;
        }
        else {
            cur++;
        }
        if(cur < 0) {
            cnt++;
        }
        min_ = min(min_, cur);
    }
    if(cur == 0 && min_ >= -1) {
        printf("Yes\n");
    }
    else {
        printf("No\n");
    }
    return 0;
}