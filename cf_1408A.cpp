#include <cstdio>
#include <vector>
using namespace std;

int main() {
    int t;
    scanf("%d", &t);
    while(t--) {
        int n;
        scanf("%d", &n);
        vector<vector<int>> val(3);
        for(int i = 0; i < 3; i++) {
            val[i].resize(n);
            for(int j = 0; j < n; j++) {
                scanf("%d", &val[i][j]);
            }
        }
        vector<int> ans(n);
        for(int i = 0; i < n; i++) {
            int pre = ans[(i + n - 1) % n];
            int nxt = ans[(i + 1) % n];
            int j = 0;
            while(val[j][i] == pre || val[j][i] == nxt) {
                j++;
            }
            ans[i] = val[j][i];
            printf("%d ", ans[i]);
        }
        printf("\n");
    }
    return 0;
}