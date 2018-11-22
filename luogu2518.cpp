#include <cstdio>
#include <cstring>
int num[105], cnt[10];
int len;
char str[105];
long long com[55][55];
long long get(int rem) {
	long long res = 1;
	for(int i = 1; i <= 9; i++) {
		if(rem < cnt[i]) return 0;
		res *= com[rem][cnt[i]];
		rem -= cnt[i];
	}
	return res;
}
int main() {
	for(int i = 0; i < 55; i++) {
		com[i][0] = 1;
		for(int j = 1; j <= i; j++) com[i][j] = com[i - 1][j - 1] + com[i - 1][j];
	}
	scanf("%s", str);
	len = strlen(str);
	for(int i = 1; i <= len; i++) {
		num[i] = str[i - 1] - '0';
		cnt[num[i]]++;
	}
	cnt[0] = 100000;
	long long ans = 0;
	for(int i = 0; i <= len; i++) {
		for(int j = 0; j < num[i]; j++) if(cnt[j] > 0) {
			cnt[j]--;
			ans += get(len - i);
			cnt[j]++;
		}
		if(--cnt[num[i]] < 0) break;
	}
	printf("%lld\n", ans);
	return 0;
}
