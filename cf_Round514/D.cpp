#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>
using namespace std;
const int MAXN = 1e5 + 5;
const long double INF = 1e15;
const long double eps = 1e-10;
int dcmp(long double x) {
	if(fabsl(x) <= eps) return 0;
	return x < 0 ? -1 : 1;
}
struct Point {
	long double x, y;
} p[MAXN];
int n;
bool check(long double y0) {
	long double l = -INF, r = INF;
	for(int i = 0; i < n; i++) {
		long double delta = p[i].y * (2 * y0 - p[i].y);
		if(dcmp(delta) < 0) return false;
		delta = sqrtl(delta);
		l = std::max(l, p[i].x - delta);
		r = std::min(r, p[i].x + delta);
	}
	return dcmp(r - l) >= 0;
}
int main() {
	cin >> n;
	bool pos = false, neg = false;
	for(int i = 0; i < n; i++) {
		cin >> p[i].x >> p[i].y;
		if(dcmp(p[i].y) < 0) neg = true;
		else pos = true;
	}
	if(neg && pos) {
		cout << "-1" << endl;
	}
	else {
		if(neg) {
			for(int i = 0; i < n; i++) p[i].y = -p[i].y;
		}
		long double l = 0, r = 1e15;
		for(int cnt = 0; cnt < 100; cnt++) {
			long double mid = (l + r) / 2;
			if(check(mid)) r = mid;
			else l = mid;
		}
		long double ans = (l + r) / 2;
		if(dcmp(ans - 1e15) == 0) cout << "-1" << endl;
		else {
			cout << setiosflags(ios::fixed) << setprecision(10) << ans << endl;
		}
	}
	return 0;
}