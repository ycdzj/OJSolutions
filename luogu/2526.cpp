#include <cstdio>
#include <cmath>
#include <vector>
#include <cstring>
using namespace std;
const double eps = 1e-8;
int dcmp(double x) {
	if(fabs(x) <= eps) return 0;
	return x < 0 ? -1 : 1;
}
struct Point {
	double x, y;
};
Point operator - (Point a, Point b) { return {a.x - b.x, a.y - b.y}; }
double sqr(double x) { return x * x; }
double dot(Point a, Point b) { return a.x * b.x + a.y * b.y; }
double len(Point a) { return sqrt(sqr(a.x) + sqr(a.y)); }
double ang(Point a, Point b) { return acos(dot(a, b) / len(a) / len(b)); }

const int MAXN = 205;
int n, m;
Point path[MAXN], dest[MAXN];
vector<int> adj[MAXN];
bool vis[MAXN];
int link[MAXN];
bool augment(int u) {
	for(int i = 0; i < adj[u].size(); i++) if(!vis[adj[u][i]]) {
		int v = adj[u][i];
		vis[v] = true;
		if(link[v] == -1 || augment(link[v])) {
			link[v] = u; link[u] = v;
			return true;
		}
	}
	return false;
}
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n; i++) scanf("%lf%lf", &path[i].x, &path[i].y);
	for(int i = 0; i < m; i++) scanf("%lf%lf", &dest[i].x, &dest[i].y);
	for(int i = 0; i + 1 < n; i++) {
		double l = len(path[i + 1] - path[i]);
		for(int j = 0; j < m; j++) {
			double l2 = len(path[i] - dest[j]) + len(path[i + 1] - dest[j]);
			if(dcmp(l2 - 2 * l) > 0) continue;
			int k;
			for(k = 0; k < m; k++) {
				Point kk = dest[k] - path[i], jj = dest[j] - path[i];
				if(dcmp(ang(kk, jj)) == 0 && len(kk) < len(jj)) break;
				kk = dest[k] - path[i + 1], jj = dest[j] - path[i + 1];
				if(dcmp(ang(kk, jj)) == 0 && len(kk) < len(jj)) break;
			}
			if(k == m) adj[i].push_back(n + j);
		}
	}
	memset(link, 0xff, sizeof(link));
	int res = 0;
	for(int i = 0; i < n; i++) {
		memset(vis, 0, sizeof(vis));
		if(augment(i)) res++;
	}
	printf("%d\n", n + res);
	for(int i = 0; i < n; i++) {
		printf("%.0f %.0f ", path[i].x, path[i].y);
		if(link[i] != -1) printf("%.0f %.0f ", dest[link[i] - n].x, dest[link[i] - n].y);
	}
	printf("\n");
	return 0;
}
