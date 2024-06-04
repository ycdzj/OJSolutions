#include <cstdio>
#include <algorithm>
#include <stack>
using namespace std;

const int MAXN = 2e5 + 5;

struct SGT {
    int val[MAXN * 4], lazy[MAXN * 4];

    void push_down(int root) {
        lazy[root << 1] += lazy[root];
        lazy[root << 1 | 1] += lazy[root];
        val[root << 1] += lazy[root];
        val[root << 1 | 1] += lazy[root];
        lazy[root] = 0;
    }
    void set(int root, int left, int right, int l, int r, int d) {
        if(r < left || right < l) {
            return;
        }
        else if(l <= left && right <= r) {
            lazy[root] = d;
            val[root] = d;
        }
        else {
            int mid = (left + right) / 2;
            push_down(root);
            set(root << 1, left, mid, l, r, d);
            set(root << 1 | 1, mid + 1, right, l, r, d);
            val[root] = max(val[root << 1], val[root << 1 | 1]);
        }
    }
    void update(int root, int left, int right, int l, int r, int d) {
        if(r < left || right < l) {
            return;
        }
        else if(l <= left && right <= r) {
            lazy[root] += d;
            val[root] += d;
        }
        else {
            int mid = (left + right) / 2;
            push_down(root);
            update(root << 1, left, mid, l, r, d);
            update(root << 1 | 1, mid + 1, right, l, r, d);
            val[root] = max(val[root << 1], val[root << 1 | 1]);
        }
    }
    int query(int root, int left, int right, int l, int r) {
        if(r < left || right < l) {
            return -1;
        }
        else if(l <= left && right <= r) {
            return val[root];
        }
        else {
            int mid = (left + right) / 2;
            push_down(root);
            return max(query(root << 1, left, mid, l, r), query(root << 1 | 1, mid + 1, right, l, r));
        }
    }
};

int n, a[MAXN];

struct MyStack {
    stack<int> stk;

    void init(int val) {
        while(!stk.empty()) {
            stk.pop();
        }
        stk.push(val);
    }
    int insert(int val) {
        while(a[stk.top()] > a[val]) { // must not be empty
            stk.pop();
        }
        int res = stk.top();
        stk.push(val);
        return res;
    }
};

int left_smaller[MAXN], right_smaller[MAXN];
int cnt_left[MAXN], cnt_right[MAXN], cnt[MAXN];
MyStack stk;
SGT sgt;

void cycle_update(int l, int r, int d) {
    l = (l + n) % n;
    r = (r + n) % n;
    if(l <= r) {
        sgt.update(1, 0, n - 1, l, r, d);
    }
    else {
        sgt.update(1, 0, n - 1, l, n - 1, d);
        sgt.update(1, 0, n - 1, 0, r, d);
    }
}

int main() {
    scanf("%d", &n);
    int pos_n, pos_1;
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        if(a[i] == 1) {
            pos_1 = i;
        }
    }
    stk.init(pos_1);
    left_smaller[pos_1] = pos_1;
    for(int i = 1; i < n; i++) {
        int idx = (pos_1 + i) % n;
        left_smaller[idx] = stk.insert(idx);
        cnt[idx] = cnt[left_smaller[idx]] + 1;
    }
    stk.init(pos_1);
    right_smaller[pos_1] = pos_1;
    for(int i = 1; i < n; i++) {
        int idx = (pos_1 + n - i) % n;
        right_smaller[idx] = stk.insert(idx);
    }
    for(int i = 0; i < n; i++) {
        if(left_smaller[i] < i) {
            cnt_left[i] = cnt_left[left_smaller[i]] + 1;
        }
    }
    for(int i = n - 1; i >= 0; i--) {
        if(right_smaller[i] > i) {
            cnt_right[i] = cnt_right[right_smaller[i]] + 1;
        }
    }
    for(int i = 0; i < n; i++) {
        sgt.update(1, 0, n - 1, i, i, cnt_left[i] + cnt_right[i]);
    }
    int ans = n, ans_idx;
    for(int i = 0; i < n; i++) {
        int cur = min(ans, sgt.query(1, 0, n - 1, 0, n - 1));
        if(cur < ans) {
            ans = cur;
            ans_idx = i;
        }
        cycle_update(i, right_smaller[i] - 1, -1);
        cycle_update(left_smaller[i] + 1, i, 1);
        sgt.set(1, 0, n - 1, i, i, cnt[i]);
    }
    printf("%d %d\n", ans + 1, ans_idx);
    return 0;
}
