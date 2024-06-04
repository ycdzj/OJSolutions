#include <cstdio>
#include <vector>
using namespace std;

int main() {
    int t;
    scanf("%d", &t);
    while(t-- > 0) {
        int n, k;
        scanf("%d%d", &n, &k);
        vector<bool> vis(n + 1);
        vector<int> seq;
        vector<int> a(n);
        for(int i = 0; i < n; i++) {
            scanf("%d", &a[i]);
            if(!vis[a[i]]) {
                vis[a[i]] = true;
                seq.push_back(a[i]);
            }
        }
        if(seq.size() > k) {
            printf("-1\n");
            continue;
        }
        while(seq.size() < k) {
            seq.push_back(seq[0]);
        }
        printf("%d\n", k * n);
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < k; j++) {
                printf("%d ", seq[j]);
            }
        }
        printf("\n");
    }
    return 0;
}