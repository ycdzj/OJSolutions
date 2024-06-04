#include <cstdio>
#include <map>
const int MAXN = 1005;
typedef long long ll;
ll gcd(ll a, ll b) {
	if(b == 0) return a;
	return gcd(b, a % b);
}
struct Point {
	ll x, y;
	bool operator < (const Point &p) const {
		if(x != p.x) return x < p.x;
		return y < p.y;
	}
};
ll f(Point a, Point b) {
	ll dx = b.x - a.x, dy = b.y - a.y;
	if(dx < 0) dx = -dx;
	if(dy < 0) dy = -dy;
	if(dx == 0) return dy + 1;
	if(dy == 0) return dx + 1;
	return gcd(dx, dy) + 1;
}
bool get(Point a, Point b, ll x, Point &res) {
	ll dx = b.x - a.x, dy = b.y - a.y;
	ll g = gcd(dx, dy);
	dx /= g; dy /= g;
	if((x - a.x) % dx == 0) {
		res.x = x;
		res.y = a.y + (x - a.x) / dx * dy;
		return true;
	}
	return false;
}
bool g(Point a, Point b, Point p, Point q, Point &res) {
	if(a.x == b.x && p.x == q.x) return false;
	if(p.x == q.x) return g(p, q, a, b, res);
	if(a.x == b.x) {
		if(!get(p, q, a.x, res)) return false;
		if(a.x > b.x) std::swap(a.x, b.x);
		if(p.x > q.x) std::swap(p.x, q.x);
		if(a.y > b.y) std::swap(a.y, b.y);
		if(p.y > q.y) std::swap(p.y, q.y);
		return a.x <= res.x && res.x <= b.x && p.x <= res.x && res.x <= q.x && a.y <= res.y && res.y <= b.y && p.y <= res.y && res.y <= q.y;
	}
	ll dx1 = b.x - a.x, dy1 = b.y - a.y;
	ll dx2 = p.x - q.x, dy2 = p.y - q.y;
	ll num = dx1 * dx2 * (p.y - a.y) - dx1 * dy2 * p.x + dy1 * dx2 * a.x;
	ll dnum = dy1 * dx2 - dy2 * dx1;
	if(dnum == 0 || num % dnum != 0) return false;
	res.x = num / dnum;
	num = dy1 * (res.x - a.x);
	dnum = dx1;
	if(dnum == 0 || num % dnum != 0) return false;
	res.y = num / dnum + a.y;
	if(a.x > b.x) std::swap(a.x, b.x);
	if(p.x > q.x) std::swap(p.x, q.x);
	if(a.y > b.y) std::swap(a.y, b.y);
	if(p.y > q.y) std::swap(p.y, q.y);
	return a.x <= res.x && res.x <= b.x && p.x <= res.x && res.x <= q.x && a.y <= res.y && res.y <= b.y && p.y <= res.y && res.y <= q.y;
}
int n;
Point a[MAXN], b[MAXN];
std::map<Point, int> cnt;
std::map<int, int> x;
int main() {
	scanf("%d", &n);
	long long ans = 0;
	for(int i = 0; i < n; i++) {
		scanf("%lld%lld%lld%lld", &a[i].x, &a[i].y, &b[i].x, &b[i].y);
		ans += f(a[i], b[i]);
		x[(i + 1) * i / 2] = i + 1;
	}
	for(int i = 0; i < n; i++) for(int j = i + 1; j < n; j++) {
		Point p;
		if(g(a[i], b[i], a[j], b[j], p)) {
			cnt[p]++;
		}
	}
	for(auto itr : cnt) {
		ans -= x[itr.second] - 1;
	}
	printf("%lld\n", ans);
	return 0;
}