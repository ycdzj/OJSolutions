#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 1e5 + 5;
const long long INF = 1e18;

int n;
vector<int> adj[MAXN];
int cost[MAXN][3];
int ans_clr[MAXN];
int seq[MAXN], cnt_seq;

void dfs(int u, int par) {
    seq[cnt_seq++] = u;
    for(int v : adj[u]) {
        if(v == par) {
            continue;
        }
        dfs(v, u);
    }
}

int main() {
    scanf("%d", &n);
    for(int clr = 0; clr < 3; clr++) {
        for(int i = 1; i <= n; i++) {
            scanf("%d", &cost[i][clr]);
        }
    }
    for(int i = 1; i < n; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    bool flag = true;
    for(int i = 1; i <= n; i++) {
        if(adj[i].size() > 2) {
            flag = false;
            break;
        }
    }
    if(!flag) {
        printf("-1\n");
    }
    else {
        for(int i = 1; i <= n; i++) {
            if(adj[i].size() == 1) {
                dfs(i, i);
                break;
            }
        }
        int p[3] = {0, 1, 2};
        long long ans = INF;
        do {
            long long cur = 0;
            for(int i = 0; i < cnt_seq; i++) {
                cur += cost[seq[i]][p[i % 3]];
            }
            if(cur < ans) {
                ans = cur;
                for(int i = 0; i < cnt_seq; i++) {
                    ans_clr[seq[i]] = p[i % 3] + 1;
                }
            }
        } while(next_permutation(p, p + 3));
        printf("%lld\n", ans);
        for(int i = 1; i <= n; i++) {
            printf("%d ", ans_clr[i]);
        }
        printf("\n");
    }
    return 0;
}
