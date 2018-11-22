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
Point operator + (Point a, Point b) { return Point(a.x + b.x, a.y + b.y); }
Point operator * (double c, Point p) { return Point(c * p.x, c * p.y); }
double det(Point a, Point b) { return a.x * b.y - a.y * b.x; }
double dot(Point a, Point b) { return a.x * b.x + a.y * b.y; }
double sqr(double x) { return x * x; }
double len(Point a) { return sqrt(sqr(a.x) + sqr(a.y)); }
Point line_intersection(Point p, Point v, Point q, Point w) {//v, w是向量
    Point u = p - q;
    double t = det(w, u) / det(v, w);
    return p + t * v;
}
int main() {
    int n; scanf("%d", &n);
    printf("INTERSECTING LINES OUTPUT\n");
    while(n--) {
        Point p1, p2, p3, p4;
        scanf("%lf%lf%lf%lf", &p1.x, &p1.y, &p2.x, &p2.y);
        scanf("%lf%lf%lf%lf", &p3.x, &p3.y, &p4.x, &p4.y);
        Point v12 = p2 - p1, v34 = p4 - p3;
        if(det(v12, v34) == 0) {
            Point v13 = p3 - p1;
            if(dcmp(len(v13)) == 0) v13 = p4 - p1;
            if(det(v12, v13) == 0) printf("LINE\n");
            else printf("NONE\n");
        }
        else {
            Point o = line_intersection(p1, v12, p3, v34);
            printf("POINT %.2f %.2f\n", o.x, o.y);
        }
    }
    printf("END OF OUTPUT\n");
    return 0;
}