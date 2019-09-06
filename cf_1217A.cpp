#include <cstdio>
#include <algorithm>
using namespace std;

int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        int s, i, e;
        scanf("%d%d%d", &s, &i, &e);
        int sum = (i + e - s + 2) / 2;
        sum = max(sum, 0);
        int ans = 0;
        if(sum <= e) {
            ans = e - sum + 1;
        }
        printf("%d\n", ans);
    }
    return 0;
}
