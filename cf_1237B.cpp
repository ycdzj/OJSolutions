#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN = 1e5 + 5;

int n;
int a[MAXN];
int pos[MAXN];

int main() {
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    for(int i = 0; i < n; i++) {
        int b;
        scanf("%d", &b);
        pos[b] = i;
    }
    int ans = 0;
    for(int max_ = -1, i = 0; i < n; i++) {
        if(max_ > pos[a[i]]) {
            ans++;
        }
        max_ = max(max_, pos[a[i]]);
    }
    printf("%d\n", ans);
    return 0;
}
