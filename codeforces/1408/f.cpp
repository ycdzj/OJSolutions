#include <cstdio>
#include <vector>
using namespace std;

vector<pair<int, int>> ans;

void f(int l, int r) {
    if (r - l <= 1) {
        return;
    }
    int mid = l + (r - l) / 2;
    f(l, mid);
    f(mid, r);
    for(int i = l; i < mid; i++) {
        ans.emplace_back(i, mid + i - l);
    }
}

int main() {
    int n;
    scanf("%d", &n);

    int x = 1;
    while(x * 2 <= n) {
        x *= 2;
    }

    f(0, x);
    f(n - x, n);

    printf("%d\n", (int)ans.size());
    for(int i = 0; i < ans.size(); i++) {
        printf("%d %d\n", ans[i].first + 1, ans[i].second + 1);
    }
    return 0;
}