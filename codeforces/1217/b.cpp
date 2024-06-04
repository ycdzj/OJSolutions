#include <cstdio>
#include <algorithm>
using namespace std;

int main() {
    int t;
    scanf("%d", &t);
    while(t--) {
        int n, x;
        scanf("%d%d", &n, &x);
        int y = 0, max_d = 0;
        for(int i = 0; i < n; i++) {
            int d, h;
            scanf("%d%d", &d, &h);
            y = max(y, d - h);
            max_d = max(max_d, d);
        }
        int ans;
        if(x <= max_d) {
            ans = 1;
        }
        else if(y == 0) {
            ans = -1;
        }
        else {
            ans = (x - max_d + y - 1) / y + 1;
        }
        printf("%d\n", ans);
    }
    return 0;
}
