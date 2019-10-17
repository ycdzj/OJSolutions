#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN = 1e5 + 5;

int n;
int a[MAXN], pos[MAXN];
int stk[MAXN], stk_top;
bool flag[MAXN];
int ans[MAXN];

void stk_insert(int idx) {
    while(stk_top < n && a[stk[stk_top]] >= a[idx]) {
        stk_top++;
    }
    stk[--stk_top] = idx;
}
int check(int val) {
    if(stk_top == n) {
        return -1;
    }
    int l = stk_top, r = n - 1;
    while(l < r) {
        int mid = (l + r) / 2;
        if(2 * a[stk[mid]] < val) {
            r = mid;
        }
        else {
            l = mid + 1;
        }
    }
    if(2 * a[stk[l]] < val) {
        return stk[l];
    }
    else {
        return -1;
    }
}

void calc_ans0() {
    int i = 0;
    while(true) {
        if(ans[0] == 2 * n) {
            break;
        }
        if(!flag[i]) {
            ans[0]++;
            if(pos[i] != -1) {
                flag[pos[i]] = true;
            }
            i = (i + 1) % n;
        }
        else {
            break;
        }
    }
}
int f(int i) {
    if(pos[i] == -1) {
        return 2 * n;
    }
    int res = pos[i] - i;
    if(res < 0) {
        res += n;
    }
    return res;
}
int que[MAXN], que_top;
void que_insert(int idx) {
    if(que_top == 0 || a[que[que_top - 1]] > a[idx]) {
        que[que_top++] = idx;
    }
}
int check_que(int val) {
    if(que_top == 0) {
        return -1;
    }
    int l = 0, r = que_top - 1;
    while(l < r) {
        int mid = (l + r) / 2;
        if(2 * a[que[mid]] < val) {
            r = mid;
        }
        else {
            l = mid + 1;
        }
    }
    if(2 * a[que[l]] < val) {
        return que[l];
    }
    else {
        return -1;
    }
}
int main() {
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    stk_top = n;
    for(int i = n - 1; i >= 0; i--) {
        pos[i] = check(a[i]);
        stk_insert(i);
    }
    for(int i = 0; i < n; i++) {
        if(pos[i] == -1) {
            pos[i] = check_que(a[i]);
        }
        que_insert(i);
    }
    calc_ans0();
    if(ans[0] == 2 * n) {
        for(int i = 0; i < n; i++) {
            ans[i] = -1;
        }
    }
    else {
        for(int i = n - 1, pre_ans = ans[0]; i > 0; i--) {
            ans[i] = min(f(i), pre_ans + 1);
            pre_ans = ans[i];
        }
    }
    for(int i = 0; i < n; i++) {
        printf("%d ", ans[i]);
    }
    printf("\n");
    return 0;
}
