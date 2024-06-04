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

const int MAXN = 1e5 + 5;
struct { Point a, b; } seg[MAXN];
int top[MAXN];
int n;
int main() {
    while(scanf("%d", &n) != EOF) {
        if(n == 0) break;
        int cnt = 0;
        for(int i = 0; i < n; i++) {
            Point a, b; scanf("%lf%lf%lf%lf", &a.x, &a.y, &b.x, &b.y);
            seg[i].a = a; seg[i].b = b;
            int cur_cnt = 0;
            for(int j = 0; j < cnt; j++) {
                if(!seg_proper_intersect(seg[top[j]].a, seg[top[j]].b, a, b)) top[cur_cnt++] = top[j];
            }
            cnt = cur_cnt;
            top[cnt++] = i;
        }
        printf("Top sticks:");
        for(int i = 0; i < cnt; i++) printf(" %d%c", top[i] + 1, (i + 1 < cnt) ? ',' : '.');
        printf("\n");
    }
    return 0;
}
