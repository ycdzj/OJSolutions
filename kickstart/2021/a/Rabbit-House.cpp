#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

const int MAXN = 305;
const int MAXM = 2e6 + 5;

int r, c;
int g[MAXN][MAXN];
bool vis[MAXN][MAXN];

int main() {
    int t;
    scanf("%d", &t);
    for(int i_case = 1; i_case <= t; i_case++) {
        scanf("%d%d", &r, &c);
        vector<pair<int, int>> idx_array;
        for(int i = 1; i <= r; i++) {
            for(int j = 1; j <= c; j++) {
                scanf("%d", &g[i][j]);
                idx_array.push_back({i, j});
                vis[i][j] = false;
            }
        }
        sort(idx_array.begin(), idx_array.end(), [](pair<int, int> x, pair<int, int> y)->bool{
            return g[x.first][x.second] > g[y.first][y.second];
        });
        int p = 0;
        long long ans = 0;
        deque<pair<int, int>> que;
        vis[idx_array[0].first][idx_array[0].second] = true;
        que.push_back(idx_array[0]);
        while(!que.empty()) {
            auto u = que.front();
            que.pop_front();
            int u_i = u.first;
            int u_j = u.second;
            while(p < idx_array.size() && g[idx_array[p].first][idx_array[p].second] >= g[u_i][u_j]) {
                auto v = idx_array[p++];
                int v_i = v.first;
                int v_j = v.second;
                if(!vis[v_i][v_j]) {
                    vis[v_i][v_j] = true;
                    que.push_front(v);
                }
            }
            if(u_i - 1 >= 1 && !vis[u_i - 1][u_j]) {
                int diff = (g[u_i][u_j] - 1) - g[u_i - 1][u_j];
                if(diff > 0) {
                    ans += diff;
                    g[u_i - 1][u_j] += diff;
                }
                vis[u_i - 1][u_j] = true;
                que.push_back({u_i - 1, u_j});
            }
            if(u_j - 1 >= 1 && !vis[u_i][u_j - 1]) {
                int diff = (g[u_i][u_j] - 1) - g[u_i][u_j - 1];
                if(diff > 0) {
                    ans += diff;
                    g[u_i][u_j - 1] += diff;
                }
                vis[u_i][u_j - 1] = true;
                que.push_back({u_i, u_j - 1});
            }
            if(u_i + 1 <= r && !vis[u_i + 1][u_j]) {
                int diff = (g[u_i][u_j] - 1) - g[u_i + 1][u_j];
                if(diff > 0) {
                    ans += diff;
                    g[u_i + 1][u_j] += diff;
                }
                vis[u_i + 1][u_j] = true;
                que.push_back({u_i + 1, u_j});
            }
            if(u_j + 1 <= c && !vis[u_i][u_j + 1]) {
                int diff = (g[u_i][u_j] - 1) - g[u_i][u_j + 1];
                if(diff > 0) {
                    ans += diff;
                    g[u_i][u_j + 1] += diff;
                }
                vis[u_i][u_j + 1] = true;
                que.push_back({u_i, u_j + 1});
            }
        }
        printf("Case #%d: %lld\n", i_case, ans);
    }
    return 0;
}