#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

long long gcd(long long a, long long b) {
    if(a == 0) {
        return b;
    }
    return gcd(b % a, a);
}

int main() {
    int t;
    scanf("%d", &t);
    while(t-- > 0) {
        int n, m;
        scanf("%d%d", &n, &m);
        vector<long long> val(n + 1);
        vector<vector<int>> adj(n + 1);
        for(int i = 1; i <= n; i++) {
            scanf("%lld", &val[i]);
        }
        for(int i = 0; i < m; i++) {
            int u, v;
            scanf("%d%d", &u, &v);
            adj[v].push_back(u);
        }
        vector<int> idx(n + 1);
        for(int i = 1; i <= n; i++) {
            sort(adj[i].begin(), adj[i].end());
            idx[i] = i;
        }
        sort(idx.begin() + 1, idx.begin() + n + 1, [&adj](int i, int j)->bool{
            return adj[i] < adj[j];
        });
        long long ans = 0;
        for(int i = 1; i <= n; ) {
            int j = i + 1;
            long long sum = val[idx[i]];
            while(j <= n && adj[idx[j]] == adj[idx[i]]) {
                sum += val[idx[j]];
                j++;
            }
            if(adj[idx[i]].size() > 0) {
                ans = gcd(ans, sum);
            }
            i = j;
        }
        printf("%lld\n", ans);
    }
    return 0;
}
