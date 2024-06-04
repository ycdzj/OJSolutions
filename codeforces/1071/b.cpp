#include <cstdio>
#include <queue>
#include <cstring>
using namespace std;
const int MAXN = 2005;
int n, k;
char board[MAXN][MAXN];
int dis[MAXN][MAXN];
bool vis[MAXN][MAXN];
bool valid(int i, int j) {
    return i < n && j < n;
}
int main() {
    scanf("%d%d", &n, &k);
    for(int i = 0; i < n; i++) scanf("%s", board[i]);
    deque<pair<int, int>> que;
    dis[0][0] = 0;
    if(board[0][0] != 'a') dis[0][0] = 1;
    vis[0][0] = true;
    que.push_front({0, 0});
    while(!que.empty()) {
        int ui = que.front().first, uj = que.front().second;
        que.pop_front();
        if(valid(ui + 1, uj) && !vis[ui + 1][uj]) {
            if(board[ui + 1][uj] == 'a') {
                dis[ui + 1][uj] = dis[ui][uj];
                vis[ui + 1][uj] = true;
                que.push_front({ui + 1, uj});
            }
            else {
                dis[ui + 1][uj] = dis[ui][uj] + 1;
                vis[ui + 1][uj] = true;
                que.push_back({ui + 1, uj});
            }
        }

        if(valid(ui, uj + 1) && !vis[ui][uj + 1]) {
            if(board[ui][uj + 1] == 'a') {
                dis[ui][uj + 1] = dis[ui][uj];
                vis[ui][uj + 1] = true;
                que.push_front({ui, uj + 1});
            }
            else {
                dis[ui][uj + 1] = dis[ui][uj] + 1;
                vis[ui][uj + 1] = true;
                que.push_back({ui, uj + 1});
            }
        }
    }
    for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) if(dis[i][j] <= k) board[i][j] = 'a';
    memset(vis, 0, sizeof(vis));
    vis[0][0] = true;
    for(int l = 0; l <= 2 * (n - 1); l++) {
        char min_ = 'z';
        for(int i = max(0, l - n + 1); i < n; i++) {
            if(vis[i][l - i]) min_ = min(min_, board[i][l - i]);
        }
        putchar(min_);
        for(int i = max(0, l - n + 1); i < n; i++) {
            if(vis[i][l - i] && board[i][l - i] == min_) {
                if(valid(i, l - i + 1)) vis[i][l - i + 1] = true;
                if(valid(i + 1, l - i)) vis[i + 1][l - i] = true;
            }
        }
    }
    return 0;
}