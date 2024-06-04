#include <cstdio>
const int MAXN = 105;
int n;
char str[MAXN];
int main() {
	scanf("%d%s", &n, str);
	int sum = 0;
	for(int i = 0; i < n; i++) sum += str[i] - '0';
	bool ans = false;
	for(int x = 1; x < sum; x++) {
		bool flag = true;
		int cur = 0;
		for(int i = 0; i < n; i++) {
			cur += str[i] - '0';
			if(cur == x) cur = 0;
			else if(cur > x) {
				flag = false;
				break;
			}
		}
		if(flag && cur == 0) {
			ans = true;
			break;
		}
	}
	if(sum == 0) ans = true;
	if(ans) printf("YES\n");
	else printf("NO\n");
	return 0;
}