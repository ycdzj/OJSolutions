#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

const int MAXN = 505;

int n;
int a[MAXN][MAXN], b[MAXN][MAXN];
int r[MAXN], c[MAXN];

int f[MAXN * 2];
int find(int x) {
    if(f[x] != x) {
        f[x] = find(f[x]);
    }
    return f[x];
}

struct Edge {
    int u, v, w;
    bool vis;
};

int main() {
    int t;
    scanf("%d", &t);
    for(int i_case = 1; i_case <= t; i_case++) {
        scanf("%d", &n);
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= n; j++) {
                scanf("%d", &a[i][j]);
            }
        }
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= n; j++) {
                scanf("%d", &b[i][j]);
            }
        }
        for(int i = 1; i <= n; i++) {
            scanf("%d", &r[i]);
        }
        for(int i = 1; i <= n; i++) {
            scanf("%d", &c[i]);
        }
        vector<Edge> edges;
        long long ans = 0;
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= n; j++) {
                if(a[i][j] == -1) {
                    Edge edge;
                    edge.u = i;
                    edge.v = n + j;
                    edge.w = b[i][j];
                    edge.vis = false;
                    ans += b[i][j];
                    edges.push_back(edge);
                }
            }
        }
        vector<int> indices(edges.size());
        for(int i = 0; i < edges.size(); i++) {
            indices[i] = i;
        }
        sort(indices.begin(), indices.end(), [&](int x, int y)->bool{
            return edges[x].w > edges[y].w;
        });
        for(int i = 1; i <= 2 * n; i++) {
            f[i] = i;
        }
        for(int i = 0; i < indices.size(); i++) {
            int e = indices[i];
            int u = find(edges[e].u);
            int v = find(edges[e].v);
            if(u != v) {
                ans -= edges[e].w;
                f[u] = v;
            }
        }
        printf("Case #%d: %lld\n", i_case, ans);
    }
    return 0;
}