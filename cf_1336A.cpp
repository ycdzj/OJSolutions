#include <iostream>
#include <numeric>
#include <algorithm>
#include <vector>
using namespace std;

const int MAXN = 2e5 + 5;

int n, k;
vector<int> adj[MAXN];
vector<int> val_list;

int dfs(int u, int par, int dep) {
	int sum = 0;
	for(int v : adj[u]) {
		if(v == par) {
			continue;
		}
		sum += dfs(v, u, dep + 1);
	}
	val_list.push_back(dep - sum);
	return sum + 1;
}

int main() {
	cin >> n >> k;
	for(int i = 1; i < n; i++) {
		int u, v;
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	dfs(1, 1, 0);
	sort(val_list.begin(), val_list.end());
	cout << accumulate(val_list.end() - k, val_list.end(), (long long)0) << endl;
	return 0;
}
