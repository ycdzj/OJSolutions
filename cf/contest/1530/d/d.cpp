#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

void solve() {
    int n;
    scanf("%d", &n);

    vector<int> a(n + 1);
    vector<bool> vis(n + 1);
    for(int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        vis[a[i]] = true;
    }

    int k = 0;
    vector<int> b(n + 1);
    vector<bool> vis2(n + 1);
    for(int i = 1; i <= n; i++) {
        if(!vis[i] && !vis2[a[i]]) {
            vis2[a[i]] = true;
            b[i] = a[i];
            k++;
        }
    }
    for(int i = 1; i <= n; i++) {
        if(!vis2[a[i]]) {
            vis2[a[i]] = true;
            b[i] = a[i];
            k++;
        }
    }

    int j = 1;
    for(int i = 2; i <= n; i++) {
        if(b[i] == 0 && vis2[i]) {
            j = i;
            break;
        }
    }

    int val = 1;
    for(int i = 1; i <= n; i++) {
        if(b[i] == 0) {
            if(i == j) {
                continue;
            }
            while(vis2[val]) {
                val++;
            }
            if(val == i) {
                b[j] = val;
                j = i;
            } else {
                b[i] = val;
            }
            val++;
        }
    }
    if(b[j] == 0) {
        while(vis2[val]) {
            val++;
        }
        b[j] = val++;
    }

    printf("%d\n", k);
    for(int i = 1; i <= n; i++) {
        printf("%d ", b[i]);
    }
    printf("\n");
}

int main() {
    int t;
    scanf("%d", &t);
    while(t--) {
        solve();
    }
    return 0;
}

