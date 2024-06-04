#include <cstdio>
#include <vector>
using namespace std;
const int MAXN = 3e5 + 5;
struct BIT {
	int time[MAXN], n, clk;
	long long tree[MAXN];
	void update(int p) {
		if(time[p] != clk) {
			time[p] = clk;
			tree[p] = 0;
		}
	}
	int lowbit(int x) { return x & (-x); }
	void modify(int p, int val) {
		while(p <= n) {
			update(p);
			tree[p] += val;
			p += lowbit(p);
		}
	}
	long long query(int p) {
		long long res = 0;
		while(p >= 1) {
			update(p);
			res += tree[p];
			p -= lowbit(p);
		}
		return res;
	}
} bit;
struct { int l, r, a; } modi[MAXN];
int n, m, k;
vector<int> land[MAXN];
int p[MAXN];
int ans[MAXN];
long long sum(int i) {
	long long res = 0;
	for(auto v : land[i]) {
		res += bit.query(v);
		if(res >= p[i]) return p[i];
	}
	return res;
}
int buf[MAXN], bufl[MAXN], bufr[MAXN];
void solve(int l, int r, int s, int t) {
	if(l == r) {
		for(int i = s; i <= t; i++) ans[buf[i]] = l;
	}
	else if(s <= t) {
		int mid = l + (r - l) / 2;
		bit.clk++;
		for(int i = l; i <= mid; i++) {
			if(modi[i].l <= modi[i].r) {
				bit.modify(modi[i].l, modi[i].a);
				bit.modify(modi[i].r + 1, -modi[i].a);
			}
			else {
				bit.modify(modi[i].l, modi[i].a);
				bit.modify(1, modi[i].a);
				bit.modify(modi[i].r + 1, -modi[i].a);
			}
		}
		int nl = 0, nr = 0;
		for(int i = s; i <= t; i++) {
			int v = buf[i];
			long long su = sum(v);
			if(su >= p[v]) bufl[nl++] = v;
			else {
				p[v] -= su;
				bufr[nr++] = v;
			}
		}
		for(int i = 0; i < nl; i++) buf[s + i] = bufl[i];
		for(int i = 0; i < nr; i++) buf[s + nl + i] = bufr[i];
		solve(l, mid, s, s + nl - 1);
		solve(mid + 1, r, s + nl, s + nl + nr - 1);
	}
}
template <typename T>
bool nxtInt(T &res) {
	char c;
	bool negative = false;
	while(c=getchar(), c!='-' && !('0'<=c && c<='9'))
		if(c == EOF) return false;
	if(c == '-') negative = true, c = getchar();
	res = 0;
	while('0'<=c && c<='9') res *= 10, res += c - '0', c = getchar();
	if(negative) res *= -1;
	return true;
}
int main() {
	nxtInt(n); nxtInt(m);
	for(int i = 1; i <= m; i++) {
		int a; nxtInt(a);
		land[a].push_back(i);
	}
	for(int i = 1; i <= n; i++) nxtInt(p[i]);
	nxtInt(k);
	for(int i = 0; i < k; i++) nxtInt(modi[i].l), nxtInt(modi[i].r), nxtInt(modi[i].a);
	for(int i = 1; i <= n; i++) buf[i] = i;
	bit.n = m;
	solve(0, k, 1, n);
	for(int i = 1; i <= n; i++) {
		if(ans[i] == k) printf("NIE\n");
		else printf("%d\n", ans[i] + 1);
	}
	return 0;
}