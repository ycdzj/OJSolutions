#include <cstdio>
#include <cmath>
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
double det(Point a, Point b) { return a.x * b.y - a.y * b.x; }
double dot(Point a, Point b) { return a.x * b.x + a.y * b.y; }

const int MAXN = 105;
Point p1[MAXN], p2[MAXN];
int n;
bool check(Point a, Point b) {
    if(dcmp(a.x - b.x) == 0 && dcmp(a.y - b.y) == 0) return false;
    Point v = b - a;
    for(int i = 0; i < n; i++) {
        Point v1 = p1[i] - a;
        Point v2 = p2[i] - a;
        if(dcmp(det(v, v1) * det(v, v2)) > 0) return false;
    }
    return true;
}
int main() {
    double x = det({1, 0}, {0, 1});
    int T; scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        for(int i = 0; i < n; i++) scanf("%lf%lf%lf%lf", &p1[i].x, &p1[i].y, &p2[i].x, &p2[i].y);
        bool ans = false;
        for(int i = 0; !ans && i < 2 * n; i++) for(int j = i + 1; j < 2 * n; j++) {
            Point a = (i < n ? p1[i] : p2[i - n]);
            Point b = (j < n ? p1[j] : p2[j - n]);
            if(check(a, b)) {
                ans = true;
                break;
            }
        }
        if(ans) printf("Yes!\n");
        else printf("No!\n");
    }
    return 0;
}