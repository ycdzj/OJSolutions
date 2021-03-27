#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

bool f[105][1005];
int g[105][1005];

vector<int> get(int i, int j) {
    if(i == 0) {
        return {};
    }
    vector<int> pre = get(i - 1, g[i][j]);
    reverse(pre.begin(), pre.begin() + j - 1 - g[i][j]);
    pre.insert(pre.begin() + j - 1 - g[i][j], 0);
    for(auto &val : pre) {
        val++;
    }
    return pre;
}

int main() {
    f[0][0] = true;
    for(int i = 1; i <= 100; i++) {
        int pre = -1;
        for(int j = 0; j <= 1001; j++) {
            if(max(0, j - i) <= pre && pre <= j - 1) {
                f[i][j] = true;
                g[i][j] = pre;
            }
            if(f[i - 1][j]) {
                pre = j;
            }
        }
    }
    int t;
    scanf("%d", &t);
    for(int i_case = 1; i_case <= t; i_case++) {
        int n, c;
        scanf("%d%d", &n, &c);
        c++;
        if(!f[n][c]) {
            printf("Case #%d: IMPOSSIBLE\n", i_case);
        } else {
            vector<int> ans = get(n ,c);
            printf("Case #%d:", i_case);
            for(auto val : ans) {
                printf(" %d", val);
            }
            printf("\n");
        }
    }
    return 0;
}