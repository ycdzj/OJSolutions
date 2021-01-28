#include <cstdio>
#include <algorithm>
const int MAXN = 3e6 + 6;
const int INF = 1e9;
int p[MAXN], dep[MAXN], f[MAXN], ans[MAXN];
bool inner[MAXN];
int n;
struct Query {
	int que[MAXN], h, t;
	int cur_l, cur_r;
	void init() {
		h = 0; t = 0;
		cur_l = 1; cur_r = 1;
	}
	int query(int l, int r) {
		for(; cur_r < r; cur_r++) {
			while(h < t && f[que[t - 1]] >= f[cur_r]) t--;
			que[t++] = cur_r;
		}
		for(; cur_l < l; cur_l++) {
			while(h < t && que[h] <= cur_l) h++;
		}
		if(h < t) return f[que[h]];
		return INF;
	}
} util[2];
int main() {
	scanf("%d", &n);
	for(int i = 2; i <= n; i++) {
		scanf("%d", &p[i]);
		dep[i] = dep[p[i]] + 1;
		inner[p[i]] = true;
	}
	util[0].init();
	for(int i = 1; i <= n; i++) {
		if(dep[i] == dep[i + 1]) {
			f[i] = std::min(dep[p[i]], util[0].query(p[i], p[i + 1]));
		}
	}

	ans[1] = INF;
	util[0].init();
	util[1].init();
	int fst = 1, lst = -1;
	for(int i = 2; i <= n; i++) {
		if(fst < p[i]) fst = p[i];
		while(fst < i && inner[fst]) fst++;
		if(!inner[i - 1]) lst = i - 1;

		ans[i] = ans[p[i]] + 1;
        if(fst < i && dep[p[i]] == dep[fst]) {
        	ans[i] = std::min(ans[i], dep[fst] + dep[i] - 2 * util[0].query(p[i], fst));
        }
        if(p[i] <= lst && dep[lst] == dep[i]) {
        	ans[i] = std::min(ans[i], dep[lst] + dep[i] - 2 * util[1].query(lst, i));
        }
	}

	for(int i = 1; i <= n; i++) {
	    if(!inner[i]) {
	    	if(ans[i] >= INF) ans[i] = -1;
	    	printf("%d %d\n", i, ans[i]);
	    }
	}
	
	return 0;
}
