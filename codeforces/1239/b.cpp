#include <cstdio>
#include <climits>
#include <algorithm>
using namespace std;

const int MAXN = 3e5 + 5;

int n;
char str[MAXN];
int s[MAXN];
int min_val;
int cnt_min;

int ans = 0, ans_l = 1, ans_r = 1;

void update(int val, int l, int r) {
    if(ans < val) {
        ans = val;
        ans_l = l;
        ans_r = r;
    }
}
void update(int l, int r) {
    swap(str[l], str[r]);
    int mi = INT_MAX;
    for(int i = 1, cur = 0; i <= n; i++) {
        int val = (str[i] == '(' ? 1 : -1);
        cur += val;
        mi = min(mi, cur);
    }
    int cnt = 0;
    for(int i = 1, cur = 0; i <= n; i++) {
        int val = (str[i] == '(' ? 1 : -1);
        cur += val;

        if(cur == mi) {
            cnt++;
        }
    }
    update(cnt, l, r);
    swap(str[l], str[r]);
}

void solve_1(int l, int r) { // -2, no m + 1
    if(r < n) {
        r++;
    }
    int ll = 0, rr = 0;
    for(int i = l; i <= r; i++) {
        if(str[i] == '(') {
            if(ll == 0) {
                ll = i;
            }
        }
        else {
            rr = i;
        }
    }
    if(ll < rr) {
        int cnt = 0;
        for(int i = ll; i < rr; i++) {
            if(s[i] == min_val + 2) {
                cnt++;
            }
        }
        update(cnt_min + cnt, ll, rr);
    }
}

void solve_2() { // + 2, m
    int l = 0, r = 0;
    for(int i = 1; i <= n; i++) {
        if(s[i] == min_val) {
            r = i;
            if(l == 0) {
                l = i;
            }
        }
    }
    int ll = 0, rr = 0;
    for(int i = l; i >= 1; i--) {
        if(str[i] == ')') {
            ll = i;
            break;
        }
    }
    for(int i = r + 1; i <= n; i++) {
        if(str[i] == '(') {
            rr = i;
            break;
        }
    }
    if(ll != 0 && rr != 0) {
        update(ll, rr);
    }
}

void solve_3(int l, int r) { // -2, contains m + 1
    if(r < n) {
        r++;
    }
    int ll = 0, rr = 0;
    for(int i = l; i <= r; i++) {
        if(str[i] == '(') {
            if(ll == 0) {
                ll = i;
            }
        }
        else {
            rr = i;
        }
    }
    if(ll < rr) {
        int cnt = 0;
        for(int i = ll; i < rr; i++) {
            if(s[i] == min_val + 1) {
                cnt++;
            }
        }
        update(cnt, ll, rr);
    }
}

void solve_4() { // +2, m and m + 1
    int l = 0, r = 0;
    for(int i = 1; i <= n; i++) {
        if(s[i] == min_val || s[i] == min_val + 1) {
            r = i;
            if(l == 0) {
                l = i;
            }
        }
    }
    int ll = 0, rr = 0;
    for(int i = l; i >= 1; i--) {
        if(str[i] == ')') {
            ll = i;
            break;
        }
    }
    for(int i = r + 1; i <= n; i++) {
        if(str[i] == '(') {
            rr = i;
            break;
        }
    }
    if(ll != 0 && rr != 0) {
        update(ll, rr);
    }
}

int main() {
    scanf("%d", &n);
    scanf("%s", str + 1);
    min_val = INT_MAX;
    for(int i = 1; i <= n; i++) {
        int val = (str[i] == '(' ? 1 : -1);
        s[i] = s[i - 1] + val;
        min_val = min(min_val, s[i]);
    }
    for(int i = 1; i <= n; i++) {
        if(s[i] == min_val) {
            cnt_min++;
        }
    }
    if(s[n] == 0) {
        ans = cnt_min;
        for(int i = 1; i <= n; ) {
            if(s[i] >= min_val + 2) {
                int l = i;
                while(i <= n && s[i] >= min_val + 2) {
                    i++;
                }
                solve_1(l, i - 1);
            }
            else {
                i++;
            }
        }
        for(int i = 1; i <= n; ) {
            if(s[i] != min_val) {
                int l = i;
                while(i <= n && s[i] != min_val) {
                    i++;
                }
                solve_3(l, i - 1);
            }
            else {
                i++;
            }
        }
        solve_2();
        solve_4();
    }
    printf("%d\n%d %d\n", ans, ans_l, ans_r);
    return 0;
}
