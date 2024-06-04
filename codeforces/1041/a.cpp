#include <cstdio>

int main() {
	int n; scanf("%d", &n);
	int max_ = 0, min_ = 1e9 + 5;
	for(int i = 0; i < n; i++) {
		int a; scanf("%d", &a);
		if(max_ < a) max_ = a;
		if(min_ > a) min_ = a;
	}
	printf("%d\n", max_ - min_ + 1 - n);
	return 0;
}