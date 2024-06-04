#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int MAXN = 305;

struct Edge {
    int v, w;
    Edge(int v_, int w_) : v(v_), w(w_) {
    }
};

struct QueNode {
    int idx, val;
    bool operator < (const QueNode &node) const {
        return val < node.val;
    }
};

class Graph {
    vector<vector<Edge>> adj;
    int n;

    vector<int> f;
    vector<vector<int>> idx;
    int find(int x) {
        if(f[x] != x) {
            f[x] = find(f[x]);
        }
        return f[x];
    }
    void merge(int x, int y) {
        x = find(x);
        y = find(y);
        if(x != y) {
            if(idx[x].size() > idx[y].size()) {
                swap(x, y);
            }
            for(int val : idx[x]) {
                idx[y].push_back(val);
            }
            f[x] = y;
        }
    }


    int ma() {
        int res;
        priority_queue<QueNode> que;
        vector<bool> vis(n);
        vector<int> val(n);
        vector<int> seq;

        que.push({find(0), 0});
        while(!que.empty()) {
            QueNode que_node = que.top();
            que.pop();
            if(vis[que_node.idx]) {
                continue;
            }
            vis[que_node.idx] = true;
            res = que_node.val;
            seq.push_back(que_node.idx);
            for(auto u : idx[que_node.idx]) {
                for(Edge e : adj[u]) {
                    int v = find(e.v);
                    if(!vis[v]) {
                        val[v] += e.w;
                        que.push({v, val[v]});
                    }
                }
            }
        }
        if(seq.size() >= 2) {
            merge(*(seq.end() - 1), *(seq.end() - 2));
        }
        return res;
    }
public:
    Graph(int n_) : n(n_) {
        adj.resize(n);
        f.resize(n);
        idx.resize(n);
        for(int i = 0; i < n; i++) {
            f[i] = i;
            idx[i].push_back(i);
        }
    }
    void add_edge(int u, int v, int w) {
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }
    int global_min_cut() {
        int res = ma();
        for(int i = 1; i < n - 1; i++) {
            res = min(res, ma());
        }
        return res;
    }
};

int cnt[MAXN][MAXN];
int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        int n, m, k;
        scanf("%d%d%d", &n, &m, &k);
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                cnt[i][j] = 0;
            }
        }
        for(int i = 0; i < m; i++) {
            int a, b;
            scanf("%d%d", &a, &b);
            cnt[--a][--b]++;
        }
        Graph g(n);
        for(int i = 0; i < n; i++) {
            for(int j = i + 1; j < n; j++) {
                int val = cnt[i][j] + cnt[j][i];
                if(val > 0) {
                    g.add_edge(i, j, val);
                }
            }
        }
        if(g.global_min_cut() >= k) {
            printf("Yes\n");
        }
        else {
            printf("No\n");
        }
    }
    return 0;
}
