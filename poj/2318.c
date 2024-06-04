#include <cstdio>
#include <cmath>
const double EPS = 1e-8;
int dcmp(double x) {
    if(fabs(x) <= EPS) return 0;
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
Point operator + (Point a, Point b) { return Point(a.x + b.x, a.y + b.y); }
Point operator * (double c, Point p) { return Point(c * p.x, c * p.y); }
Point operator / (Point p, double c) { return Point(p.x / c, p.y / c); }
double det(Point a, Point b) { return a.x * b.y - a.y * b.x; }
double dot(Point a, Point b) { return a.x * b.x + a.y * b.y; }
Point line_intersection(Point p, Point v, Point q, Point w) {
    Point u = p - q;
    double t = det(w, u) / det(v, w);
    return p + t * v;
}
bool on_seg(Point p, Point a, Point b) {
    Point v1 = a - p, v2 = b - p;
    return dcmp(det(v1, v2)) == 0 && dcmp(dot(v1, v2)) <= 0;
}
const int MAXN = 1e5 + 5;
int n, m;
double x_1, y_1, x_2, y_2;
Point sg1[MAXN], sg2[MAXN];
int cnt[MAXN];
int main() {
    bool flag = false;
    while(scanf("%d%d%lf%lf%lf%lf", &n, &m, &x_1, &y_1, &x_2, &y_2) != EOF) {
        if(n == 0) break;
        if(flag) printf("\n");
        flag = true;
        for(int i = 0; i < n; i++) {
            double u, l; scanf("%lf%lf", &u, &l);
            sg1[i] = Point(u, y_1);
            sg2[i] = Point(l, y_2);
            cnt[i] = 0;
        }
        cnt[n] = 0;
        sg1[n] = Point(x_2, y_1);
        sg2[n] = Point(x_2, y_2);
        while(m--) {
            double x, y; scanf("%lf%lf", &x, &y);
            Point a = Point(x, y), b = Point(x_2 + 10, y);
            int l = 0, r = n;
            while(l < r) {
                int mid = l + (r - l) / 2;
                if(on_seg(line_intersection(a, b - a, sg1[mid], sg2[mid] - sg1[mid]), a, b)) r = mid;
                else l = mid + 1;
            }
            cnt[l]++;
        }
        for(int i = 0; i <= n; i++) printf("%d: %d\n", i, cnt[i]);
    }

    return 0;
}