#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

struct Solver {
    int n, m;
    vector<vector<int>> adj;

    void solve() {
        scanf("%d%d", &n, &m);

        adj.assign(n, vector<int>());

        for(int i = 0; i < m; i++) {
            int u, v;
            scanf("%d%d", &u, &v);

            u--;
            v--;

            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        vector<int> clr(n, -1); // -1:unknown 0:black 1:white
        int cnt_black = 0;

        queue<int> que;
        que.push(0);

        while(!que.empty()) {
            int u = que.front();
            que.pop();

            if(clr[u] != -1) {
                continue;
            }

            clr[u] = 0;
            cnt_black++;

            for(int v : adj[u]) {
                if(clr[v] == -1) {
                    clr[v] = 1;
                    for(int w : adj[v]) {
                        if(clr[w] == -1) {
                            que.push(w);
                        }
                    }
                }
            }
        }
        
        if(find(clr.begin(), clr.end(), -1) != clr.end()) {
            printf("NO\n");
        } else {
            printf("YES\n");
            printf("%d\n", cnt_black);
            for(int i = 0; i < n; i++) {
                if(clr[i] == 0) {
                    printf("%d ", i + 1);
                }
            }
            printf("\n");
        }
    }
};

int main() {
    int t;
    scanf("%d", &t);
    while(t--) {
        Solver solver;
        solver.solve();
    }
    return 0;
}
