#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <algorithm>
const double EPS = 1e-8;
const double PI = acos(-1);
struct Point {
    double x, y;
};
Point operator - (Point a, Point b) { return {a.x - b.x, a.y - b.y}; }
double sqr(double x) { return x * x; }
double len(Point a) { return sqrt(sqr(a.x) + sqr(a.y)); }
const int MAXN = 1e4 + 5;
Point p[MAXN];
int n, w[MAXN];
double ans = 1e9;
double f(Point o) {
    double res = 0;
    for(int i = 0; i < n; i++) res += len(p[i] - o) * w[i];
    ans = std::min(ans, res);
    return res;
}
double rand01() { return (rand() % 10001) / 10000.0; }
Point anneal(Point cur) {
    const double T = 100000, STEP = 0.98;
    double t = T;
    double cur_val = f(cur);
    while(t > EPS) {
        double tmp = 2 * PI * rand01();
        Point nxt = {cur.x + t * sin(tmp), cur.y + t * cos(tmp)};

        double nxt_val = f(nxt);
        double dif = cur_val - nxt_val;//最小值
        if(dif >= 0 || exp(dif / t) >= rand01()) cur = nxt, cur_val = nxt_val;
        t *= STEP;
    }
    for(int cnt = 0; cnt < 1000; cnt++) {
        t = 0.01 * rand01();
        double tmp = 2 * PI * rand01();
        Point nxt = {cur.x + t * sin(tmp), cur.y + t * cos(tmp)};

        double nxt_val = f(nxt);
        if(nxt_val < cur_val) cur = nxt, cur_val = nxt_val;//最小值
    }
    return cur;
}

int main() {
    srand(1086);
    scanf("%d", &n);
    for(int i = 0; i < n; i++) scanf("%lf%lf%d", &p[i].x, &p[i].y, &w[i]);
    Point ans = anneal((Point){0, 0});
    printf("%.3f %.3f\n", ans.x, ans.y);
    return 0;
}