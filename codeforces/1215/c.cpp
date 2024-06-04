#include <cstdio>
#include <vector>
using namespace std;

const int MAXN = 2e5 + 5;

int n;
char s[MAXN], t[MAXN];

int main() {
    scanf("%d%s%s", &n, s, t);
    int pre_ab = -1, pre_ba = -1;
    vector<pair<int, int>> ans;
    for(int i = 0; i < n; i++) {
        if(s[i] == 'a' && t[i] == 'b') {
            if(pre_ab != -1) {
                ans.emplace_back(pre_ab, i);
                pre_ab = -1;
            }
            else {
                pre_ab = i;
            }
        }
        if(s[i] == 'b' && t[i] == 'a') {
            if(pre_ba != -1) {
                ans.emplace_back(pre_ba, i);
                pre_ba = -1;
            }
            else {
                pre_ba = i;
            }
        }
    }
    if(pre_ab != -1 || pre_ba != -1) {
        if(pre_ab == -1 || pre_ba == -1) {
            printf("-1\n");
            return 0;
        }
        else {
            ans.emplace_back(pre_ab, pre_ab);
            ans.emplace_back(pre_ab, pre_ba);
        }
    }
    printf("%d\n", (int)ans.size());
    for(int i = 0; i < ans.size(); i++) {
        printf("%d %d\n", ans[i].first + 1, ans[i].second + 1);
    }
    return 0;
}
