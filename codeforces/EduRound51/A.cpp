#include <cstdio>
#include <cstring>
char str[1005];
int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%s", str);
		int len = strlen(str);
		int visa = 0, visA = 0, vis0 = 0;
		for(int i = 0; i < len; i++) {
			if('0' <= str[i] && str[i] <= '9') vis0++;
			else if('a' <= str[i] && str[i] <= 'z') visa++;
			else if('A' <= str[i] && str[i] <= 'Z') visA++;
		}
		int cnt = 0;
		if(visa == 0) cnt++;
		if(visA == 0) cnt++;
		if(vis0 == 0) cnt++;
		if(cnt == 1) {
			int p = 0;
			if(visa >= 2) {
				for(int i = 0; i < len; i++) if('a' <= str[i] && str[i] <= 'z') {
					p = i;
					break;
				}
			}
			else if(vis0 >= 2) {
				for(int i = 0; i < len; i++) if('0' <= str[i] && str[i] <= '9') {
					p = i;
					break;
				}
			}
			else if(visA >= 2) {
				for(int i = 0; i < len; i++) if('A' <= str[i] && str[i] <= 'Z') {
					p = i;
					break;
				}
			}
			if(visa == 0) str[p] = 'a';
			else if(visA == 0) str[p] = 'A';
			else if(vis0 == 0) str[p] = '0';
		}
		else if(cnt == 2) {
			int p = 0;
			if(visa == 0) str[p++] = 'a';
			if(visA == 0) str[p++] = 'A';
			if(vis0 == 0) str[p++] = '0';
		}
		printf("%s\n", str);
	}
	return 0;
}
