#include <cstdio>
#include <deque>
using namespace std;
const int MAXN = 2005;
int n, m, r, c, x, y;
char board[MAXN][MAXN];
bool vis[MAXN][MAXN];
int dis[MAXN][MAXN];
bool valid(int i, int j) { return 0 <= i && i < n && 0 <= j && j < m && board[i][j] == '.' && !vis[i][j]; }
int main() {
	scanf("%d%d%d%d%d%d", &n, &m, &r, &c, &x, &y);
	for(int i = 0; i < n; i++) scanf("%s", board[i]);
	deque<pair<int, int>> que;
	vis[r - 1][c - 1] = true;
	que.emplace_back(r - 1, c - 1);
	while(!que.empty()) {
		auto u = que.front(); que.pop_front();
		if(valid(u.first - 1, u.second)) {
			vis[u.first - 1][u.second] = true;
			dis[u.first - 1][u.second] = dis[u.first][u.second];
			que.emplace_front(u.first - 1, u.second);
		}
		if(valid(u.first + 1, u.second)) {
			vis[u.first + 1][u.second] = true;
			dis[u.first + 1][u.second] = dis[u.first][u.second];
			que.emplace_front(u.first + 1, u.second);
		}
		if(valid(u.first, u.second + 1)) {
			vis[u.first][u.second + 1] = true;
			dis[u.first][u.second + 1] = dis[u.first][u.second] + 1;
			que.emplace_back(u.first, u.second + 1);
		}
		if(valid(u.first, u.second - 1)) {
			vis[u.first][u.second - 1] = true;
			dis[u.first][u.second - 1] = dis[u.first][u.second] + 1;
			que.emplace_back(u.first, u.second - 1);
		}
	}
	int ans = 0;
	for(int i = 0; i < n; i++) for(int j = 0; j < m; j++) if(vis[i][j]) {
		int L = ((c - 1) - j + dis[i][j]) / 2;
		int R = dis[i][j] - L;
		if(L <= x && R <= y) ans++;
	}
	printf("%d\n", ans);
	return 0;
}