#include <cstdio>
#include <vector>
using namespace std;

int count(int x) {
    for(int i = 30; i >= 0; i--) {
        if(x >> i & 1) {
            return i;
        }
    }
    return -1;
}

int main() {
    int t;
    scanf("%d", &t);
    while(t-- > 0) {
        int n;
        scanf("%d", &n);
        vector<int> a(n);
        for(int i = 0; i < n; i++) {
            scanf("%d", &a[i]);
        }
        int ans = -1;
        for(int i = 1; i < n; i++) {
            if(a[i - 1] > a[i]) {
                ans = max(ans, count(a[i - 1] - a[i]));
                a[i] = a[i - 1];
            }
        }
        printf("%d\n", ans + 1);
    }
    return 0;
}