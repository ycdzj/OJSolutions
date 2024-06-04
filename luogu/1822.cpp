#include <cstdio>
#include <queue>
int a, b;
std::queue<int> que;
long long pow10[10];
void dfs(int *buf, int cnt, int i, int pre, long long cur) {
	if(cur * pow10[cnt - i] > b) return;
	if(i == cnt) {
		que.push((int)cur);
	}
	else {
		if(buf[i] == 0) dfs(buf, cnt, i + 1, pre, cur * 10 + pre);
		else {
			if(pre + buf[i] <= 9) dfs(buf, cnt, i + 1, pre + buf[i], cur * 10 + pre + buf[i]);
			if(0 <= pre - buf[i]) dfs(buf, cnt, i + 1, pre - buf[i], cur * 10 + pre - buf[i]);
		}
	}
}
int buf[10];
int main() {
	pow10[0] = 1;
	for(int i = 1; i < 10; i++) pow10[i] = pow10[i - 1] * 10;
	scanf("%d%d", &a, &b);
	int ans = 0;
	que.push(7);
	while(!que.empty()) {
		int u = que.front(); que.pop();
		if(a <= u && u <= b) ans++;
		int top = 10;
		while(u) {
			buf[--top] = u % 10;
			u /= 10;
		}
		for(int i = 0; i < top; i++) buf[i] = 0;
		for(int i = 0; i <= top; i++) for(int j = 1; j <= 9; j++) {
			dfs(buf + i, 10 - i, 0, j, j);
		}
	}
	printf("%d\n", ans);
	return 0;
}