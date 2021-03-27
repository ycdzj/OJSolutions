#include <cstdio>
#include <stack>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int t;
    scanf("%d", &t);
    for(int i_case = 1; i_case <= t; i_case++) {
        int n;
        scanf("%d", &n);
        vector<int> a(n);
        for(int i = 0; i < n; i++) {
            scanf("%d", &a[i]);
        }
        int ans = 0;
        for(int i = 0; i < n - 1; i++) {
            int j = i;
            for(int k = i + 1; k < n; k++) {
                if(a[k] < a[j]) {
                    j = k;
                }
            }
            ans += j - i + 1;
            reverse(a.begin() + i, a.begin() + j + 1);
        }
        printf("Case #%d: %d\n", i_case, ans);
    }
    return 0;
}