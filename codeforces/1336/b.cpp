#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const long long INF = 4e18;

int cnt_r, cnt_g, cnt_b;
vector<long long> r, g, b;
long long ans;

long long sq(long long x) {
	return x * x;
}

long long calc(int i, int j, int k) {
	return sq(r[i] - g[j]) + sq(r[i] - b[k]) + sq(g[j] - b[k]);
}

void solve(int i, int j, int k) {
	for(int ii = i - 1; ii <= i; ii++) {
		for(int jj = j - 1; jj <= j; jj++) {
			for(int kk = k - 1; kk <= k; kk++) {
				if(0 <= ii && ii < cnt_r) {
					if(0 <= jj && jj < cnt_g) {
						if(0 <= kk && kk < cnt_b) {
							ans = min(ans, calc(ii, jj, kk));
						}
					}
				}
			}
		}
	}
}

int main() {
	int t;
	cin >> t;
	while(t-- > 0) {
		cin >> cnt_r >> cnt_g >> cnt_b;
		r.resize(cnt_r);
		g.resize(cnt_g);
		b.resize(cnt_b);
		for(int i = 0; i < cnt_r; i++) {
			cin >> r[i];
		}
		for(int i = 0; i < cnt_g; i++) {
			cin >> g[i];
		}
		for(int i = 0; i < cnt_b; i++) {
			cin >> b[i];
		}
		sort(r.begin(), r.end());
		sort(g.begin(), g.end());
		sort(b.begin(), b.end());

		ans = INF;
		for(int i = 0; i < cnt_r; i++) {
			int j = lower_bound(g.begin(), g.end(), r[i]) - g.begin();
			int k = lower_bound(b.begin(), b.end(), r[i]) - b.begin();
			solve(i, j, k);
		}
		for(int j = 0; j < cnt_g; j++) {
			int i = lower_bound(r.begin(), r.end(), g[j]) - r.begin();
			int k = lower_bound(b.begin(), b.end(), g[j]) - b.begin();
			solve(i, j, k);
		}
		for(int k = 0; k < cnt_b; k++) {
			int i = lower_bound(r.begin(), r.end(), b[k]) - r.begin();
			int j = lower_bound(g.begin(), g.end(), b[k]) - g.begin();
			solve(i, j, k);
		}
		
		cout << ans << endl;
	}
	return 0;
}
