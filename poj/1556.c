#include <cstdio>
#include <cmath>
#include <vector>
#include <queue>

using namespace std;
const double EPS = 1e-8;
int dcmp(double x) {
    if(fabs(x) < EPS) return 0;
    return x < 0 ? -1 : 1;
}
struct Point {
    double x, y;
    Point() {}
    Point(double x_, double y_) {
        x = x_;
        y = y_;
    }
};
Point operator - (Point a, Point b) { return Point(a.x - b.x, a.y - b.y); }
bool operator == (Point a, Point b) { return dcmp(a.x - b.x) == 0 && dcmp(a.y - b.y) == 0; }
double det(Point a, Point b) { return a.x * b.y - a.y * b.x; }
double dot(Point a, Point b) { return a.x * b.x + a.y * b.y; }
double sqr(double x) { return x * x; }
double len(Point a) { return sqrt(sqr(a.x) + sqr(a.y)); }
bool seg_proper_intersect(Point a1, Point a2, Point b1, Point b2) {
    if(a1 == b1 && a2 == b2) return true;
    if(a1 == b2 && a2 == b1) return true;
    Point va = a2 - a1, vb = b2 - b1;
    double c1 = det(va, b1 - a1);
    double c2 = det(va, b2 - a1);
    double c3 = det(vb, a1 - b1);
    double c4 = det(vb, a2 - b1);
    return dcmp(c1) * dcmp(c2) < 0 && dcmp(c3) * dcmp(c4) < 0;
}
const int MAXN = 1e4 + 5;
Point sg_a[MAXN], sg_b[MAXN];
Point p[MAXN];
vector<pair<int, double>> adj[MAXN];
double dis[MAXN];
int n, cnt_sg, cnt_p;
int main() {
    while(scanf("%d", &n) != EOF) {
        if(n == -1) break;
        cnt_sg = cnt_p = 0;
        p[cnt_p++] = Point(0, 5);
        p[cnt_p++] = Point(10, 5);
        for(int i = 0; i < n; i++) {
            double x, y[4];
            scanf("%lf", &x);
            for(int j = 0; j < 4; j++) {
                scanf("%lf", &y[j]);
                p[cnt_p++] = Point(x, y[j]);
            }
            sg_a[cnt_sg] = Point(x, 0);
            sg_b[cnt_sg++] = Point(x, y[0]);
            sg_a[cnt_sg] = Point(x, y[1]);
            sg_b[cnt_sg++] = Point(x, y[2]);
            sg_a[cnt_sg] = Point(x, y[3]);
            sg_b[cnt_sg++] = Point(x, 10);
        }
        for(int i = 0; i < cnt_p; i++) adj[i].clear(), dis[i] = 1e9;
        for(int i = 0; i < cnt_p; i++) for(int j = i + 1; j < cnt_p; j++) {
            bool flag = true;
            for(int x = 0; x < cnt_sg; x++) {
                if(seg_proper_intersect(p[i], p[j], sg_a[x], sg_b[x])) {
                    flag = false;
                    break;
                }
            }
            if(flag) {
                double l = len(p[i] - p[j]);
                adj[i].push_back(make_pair(j, l));
                adj[j].push_back(make_pair(i, l));
            }
        }
        priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> que;
        dis[0] = 0;
        que.push(make_pair(dis[0], 0));
        while(!que.empty()) {
            pair<double, int> pr = que.top(); que.pop();
            if(dis[pr.second] != pr.first) continue;
            int u = pr.second;
            for(int i = 0; i < adj[u].size(); i++) {
                int v = adj[u][i].first;
                if(dis[v] > dis[u] + adj[u][i].second) {
                    dis[v] = dis[u] + adj[u][i].second;
                    que.push(make_pair(dis[v], v));
                }
            }
        }
        printf("%.2f\n", dis[1]);
    }
    return 0;
}