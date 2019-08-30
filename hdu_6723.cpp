#include <cstdio>
#include <vector>
using namespace std;
const int MAXN = 2e5 + 5;

struct Query {
    int op;
    int ans;
} query[MAXN];

struct QueryNode {
    int idx, arg1, arg2;
};

struct Vertex {
    vector<int> adj;
    bool vis;
    bool merged;
    int par;

    vector<QueryNode> query_lca;
    vector<QueryNode> query_rank;
    vector<QueryNode> query_dep;
    void clear() {
        adj.clear();
        query_lca.clear();
        query_rank.clear();
        query_dep.clear();
        vis = false;
        merged = false;
    }
} vert[MAXN];

struct DSet {
    vector<int> f;
    DSet(int n) {
        f.resize(n);
        for(int i = 0; i < n; i++) {
            f[i] = i;
        }
    }
    void reset() {
        for(int i = 0; i < f.size(); i++) {
            f[i] = i;
        }
    }
    int find(int x) {
        if(f[x] != x) {
            f[x] = find(f[x]);
        }
        return f[x];
    }
};

int n, q;

void merge_all(DSet &d_set, int u) {
    if(vert[u].merged) {
        return;
    }
    vert[u].merged = true;
    for(int v : vert[u].adj) {
        if(v == vert[u].par) {
            continue;
        }
        if(d_set.find(u) != d_set.find(v)) {
            merge_all(d_set, v);
            d_set.f[d_set.find(v)] = d_set.find(u);
        }
    }
}

struct BIT {
    vector<int> tree;
    int n;

    BIT(int n_) {
        n = n_;
        tree.resize(n + 1);
    }

    int lowbit(int x) {
        return x & (-x);
    }
    void change(int p, int val) {
        while(p >= 1) {
            tree[p] += val;
            p -= lowbit(p);
        }
    }
    int query(int p) {
        int res = 0;
        while(p <= n) {
            res += tree[p];
            p += lowbit(p);
        }
        return res;
    }
};

void dfs_rank(BIT &bit, int u) {
    for(auto q : vert[u].query_rank) {
        query[q.idx].ans -= q.arg2 * bit.query(q.arg1 + 1);
    }
    bit.change(u, 1);
    for(int v : vert[u].adj) {
        if(v == vert[u].par) {
            continue;
        }
        dfs_rank(bit, v);
    }
    for(auto q : vert[u].query_rank) {
        query[q.idx].ans += q.arg2 * bit.query(q.arg1 + 1);
    }
}

void dfs_lca(DSet &dset, int u) {
    vert[u].vis = true;
    for(auto q : vert[u].query_lca) {
        if(vert[q.arg1].vis) {
            int lca = dset.find(q.arg1);
            vert[lca].query_dep.push_back({q.idx, -2});
        }
    }
    for(int v : vert[u].adj) {
        if(v == vert[u].par) {
            continue;
        }
        dfs_lca(dset, v);
        int fv = dset.find(v);
        dset.f[fv] = u;
    }
}

void dfs_dep(int dep, int u) {
    for(auto q : vert[u].query_dep) {
        query[q.idx].ans += dep * q.arg1;
    }
    for(int v : vert[u].adj) {
        if(v == vert[u].par) {
            continue;
        }
        dfs_dep(dep + 1, v);
    }
}
void dfs_par(int u, int par) {
    vert[u].par = par;
    for(int v : vert[u].adj) {
        if(v == par) {
            continue;
        }
        dfs_par(v, u);
    }
}
int main() {
    int t;
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        for(int i = 1; i <= n; i++) {
            vert[i].clear();
        }
        for(int i = 1; i < n; i++) {
            int u, v;
            scanf("%d%d", &u, &v);
            vert[u].adj.push_back(v);
            vert[v].adj.push_back(u);
        }
        dfs_par(1, 1);
        scanf("%d", &q);
        DSet d_set(n + 1);
        for(int i = 0; i < q; i++) {
            scanf("%d", &query[i].op);
            if(query[i].op == 1) {
                int x;
                scanf("%d", &x);
                merge_all(d_set, x);
            }
            else {
                int x, y;
                scanf("%d%d", &x, &y);
                int px = d_set.find(x);
                int py = d_set.find(y);

                if(px == py && vert[px].merged) {
                    if(x > y) {
                        swap(x, y);
                    }
                    vert[px].query_rank.push_back({i, x, 1});
                    vert[py].query_rank.push_back({i, y, -1});
                }
                else {
                    if(vert[px].merged) {
                        vert[px].query_rank.push_back({i, x, 1});
                    }
                    if(vert[py].merged) {
                        vert[py].query_rank.push_back({i, y, 1});
                    }
                    if(px != py) {
                        vert[px].query_dep.push_back({i, 1});
                        vert[py].query_dep.push_back({i, 1});

                        vert[px].query_lca.push_back({i, py});
                        vert[py].query_lca.push_back({i, px});
                    }
                }
                query[i].ans = 0;
            }
        }
        BIT bit(n + 1);
        dfs_rank(bit, 1);
        d_set.reset();
        dfs_lca(d_set, 1);
        dfs_dep(0, 1);
        for(int i = 0; i < q; i++) {
            if(query[i].op == 2) {
                printf("%d\n", query[i].ans);
            }
        }
    }
    return 0;
}
