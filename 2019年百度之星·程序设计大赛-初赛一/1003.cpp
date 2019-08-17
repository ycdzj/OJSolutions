#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int MAXN = 405;
struct QueNode {
    int v;
    double w;
    bool operator < (const QueNode &a) const {
        return w > a.w;
    }
};
struct Graph {
    vector<pair<int, double>> adj[MAXN * MAXN];
    double dis[MAXN * MAXN];
    void add_edge(int u, int v, double w) {
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
    double dijkstra(int s, int t) {
        priority_queue<QueNode> que;

        dis[s] = 0;
        que.push({s, dis[s]});

        while(!que.empty()) {
            QueNode node = que.top();
            que.pop();
            if(dis[node.v] < node.w) {
                continue;
            }
            for(auto pr : adj[node.v]) {
                if(dis[pr.first] > node.w + pr.second) {
                    dis[pr.first] = node.w + pr.second;
                    que.push({pr.first, dis[pr.first]});
                }
            }
        }

        return dis[t];
    }
} G;

struct Rectangle {
    int x1, y1, x2, y2;
};

int n;
Rectangle rect[MAXN];
vector<Rectangle> ins_x[MAXN], del_x[MAXN], ins_y[MAXN], del_y[MAXN];
int x[MAXN], y[MAXN], cnt_x, cnt_y;
int xa, ya, xb, yb;
int sum[MAXN];

int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        cnt_x = 0;
        cnt_y = 0;

        scanf("%d", &n);
        for(int i = 0; i < n; i++) {
            int x1, y1, x2, y2;
            scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
            rect[i] = {x1, y1, x2, y2};
            x[cnt_x++] = x1;
            x[cnt_x++] = x2;
            y[cnt_y++] = y1;
            y[cnt_y++] = y2;
        }
        scanf("%d%d%d%d", &xa, &ya, &xb, &yb);
        x[cnt_x++] = xa;
        x[cnt_x++] = xb;
        y[cnt_y++] = ya;
        y[cnt_y++] = yb;

        sort(x, x + cnt_x);
        cnt_x = unique(x, x + cnt_x) - x;
        sort(y, y + cnt_y);
        cnt_y = unique(y, y + cnt_y) - y;

        for(int i = 0; i < cnt_x; i++) {
            ins_x[i].clear();
            del_x[i].clear();
        }
        for(int j = 0; j < cnt_y; j++) {
            ins_y[j].clear();
            del_y[j].clear();
        }

        for(int i = 0; i < n; i++) {
            int x1 = lower_bound(x, x + cnt_x, rect[i].x1) - x;
            int x2 = lower_bound(x, x + cnt_x, rect[i].x2) - x;
            int y1 = lower_bound(y, y + cnt_y, rect[i].y1) - y;
            int y2 = lower_bound(y, y + cnt_y, rect[i].y2) - y;
            ins_x[x1].push_back({x1, y1, x2, y2});
            del_x[x2 + 1].push_back({x1, y1, x2, y2});
            ins_y[y1].push_back({x1, y1, x2, y2});
            del_y[y2 + 1].push_back({x1, y1, x2, y2});
        }

        for(int i = 0; i < cnt_x * cnt_y; i++) {
            G.adj[i].clear();
            G.dis[i] = 5e9;
        }
        for(int i = 0; i < cnt_x; i++) {
            sum[i] = 0;
        }
        for(int j = 0; j < cnt_y; j++) {
            for(auto pr : ins_y[j]) {
                sum[pr.x1]++;
                sum[pr.x2]--;
            }
            for(auto pr : del_y[j]) {
                sum[pr.x1]--;
                sum[pr.x2]++;
            }
            for(int i = 0, cur_sum = 1; i + 1 < cnt_x; i++) {
                cur_sum += sum[i];
                G.add_edge(i * cnt_y + j, (i + 1) * cnt_y + j, 1.0 * (x[i + 1] - x[i]) / cur_sum);
            }
        }
        for(int i = 0; i < cnt_y; i++) {
            sum[i] = 0;
        }
        for(int i = 0; i < cnt_x; i++) {
            for(auto pr : ins_x[i]) {
                sum[pr.y1]++;
                sum[pr.y2]--;
            }
            for(auto pr : del_x[i]) {
                sum[pr.y1]--;
                sum[pr.y2]++;
            }
            for(int j = 0, cur_sum = 1; j + 1 < cnt_y; j++) {
                cur_sum += sum[j];
                G.add_edge(i * cnt_y + j, i * cnt_y + j + 1, 1.0 * (y[j + 1] - y[j]) / cur_sum);
            }
        }
        xa = lower_bound(x, x + cnt_x, xa) - x;
        xb = lower_bound(x, x + cnt_x, xb) - x;
        ya = lower_bound(y, y + cnt_y, ya) - y;
        yb = lower_bound(y, y + cnt_y, yb) - y;
        printf("%.5lf\n", G.dijkstra(xa * cnt_y + ya, xb * cnt_y + yb));
    }
    return 0;
}
