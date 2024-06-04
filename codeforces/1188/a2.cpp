#include <iostream>
#include <vector>
using namespace std;

struct Edge {
    int u, v;
    int w;
    int leaf;

    Edge(int u_, int v_, int w_, int leaf_)
    : u(u_)
    , v(v_)
    , w(w_)
    , leaf(leaf_) {

    }
};

struct Operation {
    int u, v, x;

    Operation(int u_, int v_, int x_)
    : u(u_)
    , v(v_)
    , x(x_) {

    }
};

struct Graph {
    vector<vector<Edge>> adj;
    vector<Operation> ans;
    int n;

    Graph(int n_)
    : n(n_) {
        adj.resize(n);
    }
    void addEdge(int u, int v, int w) {
        adj[u].push_back(Edge(u, v, w, -1));
        adj[v].push_back(Edge(v, u, 0, -1));
    }

    int getLeaf(int u, int idx) {
        if(adj[u][idx].leaf != -1) {
            return adj[u][idx].leaf;
        }
        int root = adj[u][idx].v;
        if(adj[root].size() == 1) {
            return adj[u][idx].leaf = root;
        }
        for(int i = 0; i < adj[root].size(); i++) {
            int v = adj[root][i].v;
            if(v != u) {
                return adj[u][idx].leaf = getLeaf(root, i);
            }
        }
    }
    void get2Leaf(int par, int u, int &l1, int &l2) {
        if(adj[u].size() == 1) {
            l1 = u;
            l2 = u;
        }
        else if(adj[u].size() >= 3) {
            int i = 0, m = adj[u].size();
            while(adj[u][i].v == par || adj[u][(i + 1) % m].v == par) {
                i++;
            }
            l1 = getLeaf(u, i);
            l2 = getLeaf(u, (i + 1) % m);
        }
    }
    void addAns(int u1, int u2, int x) {
        if(u1 != u2) {
            ans.push_back(Operation(u1, u2, x));
        }
    }
    void calcAnswer() {
        for(int u = 0; u < n; u++) {
            for(int i = 0; i < adj[u].size(); i++) {
                if(adj[u][i].w > 0) {
                    int v = adj[u][i].v;
                    int u1, u2, v1, v2;
                    get2Leaf(v, u, u1, u2);
                    get2Leaf(u, v, v1, v2);
                    addAns(u1, v1, adj[u][i].w / 2);
                    addAns(u2, v2, adj[u][i].w / 2);
                    addAns(u1, u2, -adj[u][i].w / 2);
                    addAns(v1, v2, -adj[u][i].w / 2);
                }
            }
        }
    }
};

int main() {
    int n;
    cin >> n;
    Graph graph(n);
    for(int i = 0; i < n - 1; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        graph.addEdge(--u, --v, w);
    }
    for(int i = 0; i < n; i++) {
        if(graph.adj[i].size() == 2) {
            cout << "NO" << endl;
            return 0;
        }
    }
    cout << "YES" << endl;
    graph.calcAnswer();
    cout << graph.ans.size() << endl;
    for(auto op : graph.ans) {
        cout << op.u + 1 << ' ' << op.v + 1 << ' ' << op.x << endl;
    }
    return 0;
}
