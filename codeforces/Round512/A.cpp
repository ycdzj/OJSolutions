#include <cstdio>

int main() {
	int n; scanf("%d", &n);
	bool ans = true;
	for(int i = 0; i < n; i++) {
		int a; scanf("%d", &a);
		if(a == 1) ans = false;
	}
	if(ans) printf("EASY\n");
	else printf("HARD\n");
	return 0;
}