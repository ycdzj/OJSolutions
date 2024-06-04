#include <cstdio>
#include <map>
using namespace std;

const int MAXN = 2e5 + 5;
const long long INF = 1e18;
struct SgtNode {
    long long min, mask;
    int minIdx;
} tree[MAXN * 4];

void pushDown(int root) {
    if(tree[root].mask != 0) {
        long long val = tree[root].mask;
        tree[root << 1].mask += val;
        tree[root << 1].min += val;
        tree[root << 1 | 1].mask += val;
        tree[root << 1 | 1].min += val;
        tree[root].mask = 0;
    }
}
void change(int root, int left, int right, int l, int r, long long val) {
    if(right < l || r < left) {
        return;
    }
    if(l <= left && right <= r) {
        tree[root].mask += val;
        tree[root].min += val;
    }
    else {
        int mid = (left + right) / 2;
        pushDown(root);
        change(root << 1, left, mid, l, r, val);
        change(root << 1 | 1, mid + 1, right, l, r, val);
        if(tree[root << 1].min < tree[root << 1 | 1].min) {
            tree[root].min = tree[root << 1].min;
            tree[root].minIdx = tree[root << 1].minIdx;
        }
        else {
            tree[root].min = tree[root << 1 | 1].min;
            tree[root].minIdx = tree[root << 1 | 1].minIdx;
        }
    }
}
pair<long long, int> query(int root, int left, int right, int l, int r) {
    if(right < l || r < left) {
        return {INF, -1};
    }
    if(l <= left && right <= r) {
        return {tree[root].min, tree[root].minIdx};
    }
    else {
        int mid = (left + right) / 2;
        pushDown(root);
        pair<long long, int> lres = query(root << 1, left, mid, l, r);
        pair<long long, int> rres = query(root << 1 | 1, mid + 1, right, l, r);
        if(lres.first < rres.first) {
            return lres;
        }
        else {
            return rres;
        }
    }
}

int n;
long long s[MAXN];
int p[MAXN];

void build(int root, int left, int right) {
    if(left == right) {
        tree[root].mask = s[left];
        tree[root].min = s[left];
        tree[root].minIdx = left;
    }
    else {
        int mid = (left + right) / 2;
        build(root << 1, left, mid);
        build(root << 1 | 1, mid + 1, right);
        if(tree[root << 1].min < tree[root << 1 | 1].min) {
            tree[root].min = tree[root << 1].min;
            tree[root].minIdx = tree[root << 1].minIdx;
        }
        else {
            tree[root].min = tree[root << 1 | 1].min;
            tree[root].minIdx = tree[root << 1 | 1].minIdx;
        }
    }
}
int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) {
        scanf("%lld", &s[i]);
    }
    build(1, 1, n);
    for(int i = 1; i <= n; i++) {
        pair<long long, int> res = query(1, 1, n, 1, n);
        p[res.second] = i;
        change(1, 1, n, res.second, res.second, INF);
        if(res.second + 1 <= n) {
            change(1, 1, n, res.second + 1, n, -i);
        }
    }
    for(int i = 1; i <= n; i++) {
        printf("%d ", p[i]);
    }
    printf("\n");
    return 0;
}
