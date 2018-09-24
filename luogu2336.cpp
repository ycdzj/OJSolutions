#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>

const int MAXN = 2.5e6 + 5;
void count(int *a, int *b, int *val, int n, int m) {//[0, n) [0, m]
	static int cnt[MAXN];
	for(int i = 0; i <= m; i++) cnt[i] = 0;
	for(int i = 0; i < n; i++) cnt[val[a[i]]]++;
	for(int i = 1; i <= m; i++) cnt[i] += cnt[i - 1];
	for(int i = n - 1; i >= 0; i--) b[--cnt[val[a[i]]]] = a[i];
}
void da(int *str, int *sa, int *rank, int n, int m) {
	static int sa_[MAXN];
	for(int i = 0; i < n; i++) sa_[i] = i;
	for(int i = 0; i < n; i++) rank[i] = str[i];
	count(sa_, sa, rank, n, m);
	for(int k = 0; (1 << k) < n; k++) {
		int l = (1 << k), p = 0;
		for(int i = n - l; i < n; i++) sa_[p++] = i;
		for(int i = 0; i < n; i++) if(sa[i] >= l) sa_[p++] = sa[i] - l;
		count(sa_, sa, rank, n, m);
		int *rank_ = sa_;
		m = 0;
		for(int i = 0; i < n; i++) {
			if(i > 0) {
				if(rank[sa[i]] != rank[sa[i - 1]]) m++;
				else if(sa[i - 1] + l >= n) m++;
				else if(rank[sa[i] + l] != rank[sa[i - 1] + l]) m++;
			}
			rank_[sa[i]] = m;
		}
		for(int i = 0; i < n; i++) rank[i] = rank_[i];
		if(m >= n - 1) break;
	}
}
void calc_height(int *str, int *sa, int *rank, int *height, int n) {
	str[n] = -1; //字符串尾需有结束符
	for(int i = 0; i < n; i++) rank[sa[i]] = i;
	height[0] = 0;
	for(int i = 0, k = 0; i < n; i++) {
		if(k > 0) k--;
		if(rank[i] != 0) {
			while(str[i + k] == str[sa[rank[i] - 1] + k]) k++;
			height[rank[i]] = k;
		}
	}
}
int n, m, idx[MAXN];
int buf[MAXN], clr[MAXN], cnt;
int sa[MAXN], rank[MAXN], height[MAXN];
struct ZKW {
	int tree[MAXN * 2], n;
	void update(int p, int val) {
		tree[p += n] = val;
		for(p >>= 1; p > 0; p >>= 1) tree[p] = std::min(tree[p << 1], tree[p << 1 | 1]);
	}
	int query(int l, int r) {
		l += n; r += n;
		int res = tree[r];
		for(; l < r; l >>= 1, r >>= 1) {
			if(l & 1) res = std::min(res, tree[l++]);
			if(r & 1) res = std::min(res, tree[--r]);
		}
		return res;
	}
} zkw;
struct AddZKW {
	int tree[MAXN * 2], n;
	void clear() {
		memset(tree, 0, sizeof(tree));
	}
	void add(int p, int val) {
		tree[p += n] += val;
		for(p >>= 1; p > 0; p >>= 1) tree[p] = tree[p << 1] + tree[p << 1 | 1];
	}
	int query(int l, int r) {
		l += n; r += n;
		int res = tree[r];
		for(; l < r; l >>= 1, r >>= 1) {
			if(l & 1) res += tree[l++];
			if(r & 1) res += tree[--r];
		}
		return res;
	}
} addzkw;
struct Query {
	int l, r, idx;
};
bool cmp(const Query &x, const Query &y) {
	if(x.l != y.l) return x.l < y.l;
	return x.r < y.r;
}
std::vector<Query> query;
int ans_m[MAXN], ans_n[MAXN];
void build_query() {
	zkw.n = cnt;
	for(int i = 0; i < cnt; i++) zkw.update(i, height[i]);
	for(int i = 0; i < m; i++) {
		int id = rank[idx[i]];
		int val = idx[i + 1] - idx[i] - 1;
		int l0 = 0, r0 = id;
		while(l0 < r0) {
			int mid = (l0 + r0) / 2;
			if(zkw.query(mid + 1, id) >= val) r0 = mid;
			else l0 = mid + 1;
		}
		int l1 = id, r1 = cnt - 1;
		while(l1 < r1) {
			int mid = (l1 + r1 + 1) / 2;
			if(zkw.query(id + 1, mid) >= val) l1 = mid;
			else r1 = mid - 1;
		}
		query.push_back({l0, l1, i});
	}
}
int pre[MAXN], pre_[MAXN];
void solve() {
	std::sort(query.begin(), query.end(), cmp);
	memset(pre, 0xff, sizeof(pre));
	addzkw.n = cnt;
	for(int i = query.size() - 1, l = cnt - 1; i >= 0; i--) {
		while(l >= query[i].l) {
			if(pre[clr[sa[l]]] != -1) addzkw.add(pre[clr[sa[l]]], -1);
			pre[clr[sa[l]]] = l;
			addzkw.add(l, 1);
			l--;
		}
		ans_m[query[i].idx] = addzkw.query(query[i].l, query[i].r) - 1;
	}
	for(int i = 0; i <= n; i++) pre[i] = cnt;
	for(int i = cnt - 1; i >= 0; i--) {
		pre_[i] = pre[clr[sa[i]]];
		pre[clr[sa[i]]] = i;
	}
	addzkw.n = cnt;
	addzkw.clear();
	for(int i = 0, j = 0; i < cnt; i++) {
		while(j < query.size() && query[j].l <= i) addzkw.add(query[j++].r, 1);
		ans_n[clr[sa[i]]] += addzkw.query(i, pre_[i] - 1);
	}
}
void ins(int c) {
	int l; scanf("%d", &l);
	while(l--) scanf("%d", &buf[cnt]), clr[cnt++] = c;
	buf[cnt] = 10001; clr[cnt++] = n;
}
int main() {
	cnt = 0;
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n; i++) ins(i), ins(i);
	for(int i = 0; i < m; i++) idx[i] = cnt, ins(n);
	idx[m] = cnt;
	da(buf, sa, rank, cnt, 10001);
	calc_height(buf, sa, rank, height, cnt);
	build_query();
	solve();
	for(int i = 0; i < m; i++) printf("%d\n", ans_m[i]);
	for(int i = 0; i < n; i++) printf("%d%c", ans_n[i], (i + 1 < n) ? ' ' : '\n');
	return 0;
}