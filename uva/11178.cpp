#include <cstdio>
#include <cmath>
const double eps = 1e-8;
const double PI = acos(-1);
int dcmp(double x) {
	if(fabs(x) <= eps) return 0;
	return x < 0 ? -1 : 1;
}
struct Point {
	double x, y;
};
Point operator - (Point a, Point b) { return {a.x - b.x, a.y - b.y}; }
Point operator + (Point a, Point b) { return {a.x + b.x, a.y + b.y}; }
Point operator * (double c, Point p) { return {c * p.x, c * p.y}; }
double sqr(double x) { return x * x; }
double len(Point a) { return sqrt(sqr(a.x) + sqr(a.y)); }
double det(Point a, Point b) { return a.x * b.y - a.y * b.x; }
double dot(Point a, Point b) { return a.x * b.x + a.y * b.y; }
double ang(Point a, Point b) { return acos(dot(a, b) / len(a) / len(b)); }
Point rotate(Point p, double A) {//逆时针旋转
	double tx = p.x, ty = p.y;
	return {tx * cos(A) - ty * sin(A), tx * sin(A) + ty * cos(A)};
}
Point line_intersect(Point p, Point v, Point q, Point w) {
	Point u = p - q;
	double t = det(w, u) / det(v, w);
	return p + t * v;
}
Point solve(Point a, Point b, Point c) {
	Point ab = b - a, ac = c - a, ba = a - b, bc = c - b;
	Point va = rotate(ab, ang(ab, ac) / 3);
	Point vb = rotate(ba, -ang(ba, bc) / 3);
	return line_intersect(a, va, b, vb);
}

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		Point a, b, c;
		scanf("%lf%lf", &a.x, &a.y);
		scanf("%lf%lf", &b.x, &b.y);
		scanf("%lf%lf", &c.x, &c.y);
		Point f = solve(a, b, c), d = solve(b, c, a), e = solve(c, a, b);
		printf("%.6f %.6f %.6f %.6f %.6f %.6f\n", d.x, d.y, e.x, e.y, f.x, f.y);
	}
	return 0;
}