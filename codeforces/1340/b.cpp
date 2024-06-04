#include <cstdio>

const int MAXN = 2005;

int check(char *from, char *to) {
	int cnt = 0;
	for(int i = 0; i < 7; i++) {
		if(from[i] == '1') {
			if(to[i] == '0') {
				return -1;
			}
		} else {
			if(to[i] == '1') {
				cnt++;
			}
		}
	}
	return cnt;
}

char digit[10][10] = {"1110111", "0010010", "1011101", "1011011", "0111010", "1101011", "1101111", "1010010", "1111111", "1111011"};

int n, k;
char str[MAXN][10];
bool f[MAXN][MAXN];

int main() {
	scanf("%d%d", &n, &k);
	for(int i = 0; i < n; i++) {
		scanf("%s", str[i]);
	}

	f[n][0] = true;
	for(int i = n - 1; i >= 0; i--) {
		for(int val = 0; val < 10; val++) {
			int c = check(str[i], digit[val]);
			if(c == -1) {
				continue;
			}
			for(int j = 0; j <= k; j++) {
				if(j - c >= 0 && f[i + 1][j - c]) {
					f[i][j] = true;
				}
			}
		}
	}
	if(!f[0][k]) {
		printf("%d\n", -1);
	} else {
		for(int i = 0; i < n; i++) {
			for(int val = 9; val >= 0; val--) {
				int c = check(str[i], digit[val]);
				if(c == -1) {
					continue;
				}
				if(k - c >= 0 && f[i + 1][k - c]) {
					printf("%d", val);
					k -= c;
					break;
				}
			}
		}
		printf("\n");
	}
	return 0;
}
