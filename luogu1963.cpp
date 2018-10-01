#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
const int MAXN = 20000 + 5;
vector<int> adj[MAXN];
int n;
bool vis[MAXN];
int link[MAXN];
bool augment(int u) {
	for(int i = 0; i < adj[u].size(); i++) if(!vis[adj[u][i]]) {
		vis[adj[u][i]] = true;
		if(link[adj[u][i]] == -1 || augment(link[adj[u][i]])) {
			link[adj[u][i]] = u; link[u] = adj[u][i];
			return true;
		}
	}
	return false;
}
int hungarian() {
	memset(link, 0xff, sizeof(link));
	int res = 0;
	for(int i = n; i >= 0; i--) {
		memset(vis, 0, sizeof(vis));
		if(augment(i)) res++;
	}
	return res;
}
int main() {
	scanf("%d", &n);
	for(int i = 0; i < n; i++) {
		int t; scanf("%d", &t);
		adj[i].push_back(n + (i + t) % n);
		adj[i].push_back(n + (i + n - t) % n);
		if(adj[i][0] > adj[i][1]) swap(adj[i][0], adj[i][1]);
	}
	if(hungarian() == n) {
		for(int i = 0; i < n; i++) printf("%d%c", link[i] - n, (i + 1 < n) ? ' ' : '\n');
	}
	else {
		printf("No Answer\n");
	}
	return 0;
}
