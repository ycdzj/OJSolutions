#include <cstdio>
#include <stack>
#include <string>
#include <cstring>
#include <vector>
using namespace std;
const int MAXN = 1e5 + 5;
char str[MAXN];
int len;
struct Res {
	long long min_, max_;
};
int skp[MAXN];
Res solve(int l, int r) {
	vector<pair<char, Res>> v, w;
	long long pre = 0;
	bool flag = false;
	for(int i = l; i <= r; i++) {
		if('0' <= str[i] && str[i] <= '9') {
			pre = pre * 10 + (str[i] - '0');
			flag = true;
		}
		else {
			if(flag) {
				v.push_back({'n', {pre, pre}});
				pre = 0;
				flag = false;
			}
			if(str[i] == '(') {
				v.push_back({'n', solve(i + 1, skp[i] - 1)});
				i = skp[i];
			}
			else {
				v.push_back({str[i], {0, 0}});
			}
		}
	}
	if(flag) v.push_back({'n', {pre, pre}});

	for(int i = 0; i < v.size(); i++) {
		while(i < v.size() && v[i].first == 'd') {
			w.back().second.max_ *= v[i + 1].second.max_;
			i += 2;
		}
		if(i >= v.size()) break;
		w.push_back(v[i]);
	}

	v.clear();
	for(int i = 0; i < w.size(); i++) {
		while(i < w.size() && w[i].first == '*') {
			long long a[2] = {v.back().second.min_, v.back().second.max_};
			long long b[2] = {w[i + 1].second.min_, w[i + 1].second.max_};
			long long max_ = -1e18, min_ = 1e18;
			for(int x = 0; x < 2; x++) for(int y = 0; y < 2; y++) {
				max_ = max(max_, a[x] * b[y]);
				min_ = min(min_, a[x] * b[y]);
			}
			v.back().second.min_ = min_; v.back().second.max_ = max_;
			i += 2;
		}
		if(i >= w.size()) break;
		v.push_back(w[i]);
	}
	long long rmin = v[0].second.min_, rmax = v[0].second.max_;
	for(int i = 2; i < v.size(); i++) {
		if(v[i - 1].first == '+') {
			rmax += v[i].second.max_;
			rmin += v[i].second.min_;
		}
		else {
			rmax -= v[i].second.min_;
			rmin -= v[i].second.max_;
		}
	}
	return {rmin, rmax};
}
stack<int> pre;
int main() {
	while(scanf("%s", str) != EOF) {
		len = strlen(str);
		for(int i = 0; i < len; i++) {
			if(str[i] == '(') pre.push(i);
			else if(str[i] == ')') {
				int j = pre.top(); pre.pop();
				skp[i] = j; skp[j] = i;
			}
			else skp[i] = i;
		}
		Res res = solve(0, len - 1);
		printf("%lld %lld\n", res.min_, res.max_);
	}
	return 0;
}