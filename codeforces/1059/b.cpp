#include <cstdio>
const int MAXN = 1e3 + 5;
int n, m;
char board[MAXN][MAXN];
bool check(int i, int j) {
	for(int di = -1; di <= 1; di++) for(int dj = -1; dj <= 1; dj++) {
		if(di == 0 && dj == 0) continue;
		int nxt_i = i + di, nxt_j = j + dj;
		if(0 <= nxt_i && nxt_i < n && 0 <= nxt_j && nxt_j < m) {
			if(board[nxt_i][nxt_j] == '.') return false;
		}
		else {
			return false;
		}
	}
	return true;
}
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n; i++) scanf("%s", board[i]);
	bool ans = true;
	for(int i = 0; ans && i < n; i++) for(int j = 0; j < m; j++) if(board[i][j] == '#') {
		bool flag = false;
		for(int di = -1; !flag && di <= 1; di++) for(int dj = -1; dj <= 1; dj++) {
			if(di == 0 && dj == 0) continue;
			int nxt_i = i + di, nxt_j = j + dj;
			if(0 <= nxt_i && nxt_i < n && 0 <= nxt_j && nxt_j < m) {
				if(check(nxt_i, nxt_j)) {
					flag = true;
					break;
				}
			}
		}
		if(!flag) {
			ans = false;
			break;
		}
	}
	if(ans) printf("YES\n");
	else printf("NO\n");
	return 0;
}