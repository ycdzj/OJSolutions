#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;
char board[30][30];
vector<pair<int, int>> a, b;
int v[]={0,0,0,0,0,0,10000,36,720,360,80,252,108,72,54,180,72,180,119,36,360,1080,144,1800,3600};
long long row[3], col[3], dig[2];
int hcnt;
bool hvis[10];
void h(int idx) {
	if(idx == b.size()) {
		hcnt++;
		for(int i = 0; i < 3; i++) {
			int sum = 0;
			for(int j = 0; j < 3; j++) sum += board[i][j] - '0';
			row[i] += v[sum];
		}
		for(int j = 0; j < 3; j++) {
			int sum = 0;
			for(int i = 0; i < 3; i++) sum += board[i][j] - '0';
			col[j] += v[sum];
		}
		dig[0] += v[board[0][0] + board[1][1] + board[2][2] - '0' * 3];
		dig[1] += v[board[0][2] + board[1][1] + board[2][0] - '0' * 3];
	}
	else {
		for(int x = 1; x <= 9; x++) {
			if(!hvis[x]) {
				board[b[idx].first][b[idx].second] = '0' + x;
				hvis[x] = true;
				h(idx + 1);
				hvis[x] = false;
			}
		}
	}
}
bool vis[10];
double g() {
	for(int i = 0; i < 3; i++) row[i] = col[i] = 0;
	dig[0] = dig[1] = 0;
	hcnt = 0;
	for(int i = 1; i <= 9; i++) hvis[i] = vis[i];
	h(0);
	long long max_ = 0;
	for(int i = 0; i < 3; i++) {
		max_ = max(max_, row[i]);
		max_ = max(max_, col[i]);
	}
	max_ = max(max_, dig[0]);
	max_ = max(max_, dig[1]);
	return (double)max_ / hcnt;
}
double sum; int cnt;
void f(int i) {
	if(i == a.size()) {
		sum += g();
		cnt++;
	}
	else {
		for(int x = 1; x <= 9; x++) if(!vis[x]) {
			board[a[i].first][a[i].second] = '0' + x;
			vis[x] = true;
			f(i + 1);
			vis[x] = false;
		}
	}
}
int main() {
	int T; scanf("%d", &T);
	while(T--) {
		for(int i = 0; i < 3; i++) scanf("%s", board[i]);
		a.clear(); b.clear();
		memset(vis, 0, sizeof(vis));
		memset(hvis, 0, sizeof(hvis));
		for(int i = 0; i < 3; i++) for(int j = 0; j < 3; j++) {
			if(board[i][j] == '*') a.emplace_back(i, j);
			if(board[i][j] == '#') b.emplace_back(i, j);
			else {
				vis[board[i][j] - '0'] = hvis[board[i][j] - '0'] = true;
			}
		}
		sum = 0; cnt = 0;
		f(0);
		printf("%.7f\n", sum / cnt);
	}
	return 0;
}
