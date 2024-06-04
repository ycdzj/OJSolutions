#include <cstdio>
#include <algorithm>
using namespace std;
int n;
char str[100005];

int main() {
    int t;
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        scanf("%s", str);
        int ans = n;
        for(int i = 0; i < n; i++) {
            if(str[i] == '1') {
                ans = max(ans, 2 * max(i + 1, n - i));
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
