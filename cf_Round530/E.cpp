#include <iostream>
using namespace std;
const int MAXN = 3e5 + 5;
int board[MAXN];
int n, m;
inline int get(int i, int j) { return board[i * m + j]; }
int check_row(int x0, int x1, int i) {
    int res = 0;
    for(int j = 0; j < m; j += 2) {
        if(get(i, j) != x0) res++;
    }
    for(int j = 1; j < m; j += 2) {
        if(get(i, j) != x1) res++;
    }
    return res;
}
int check_col(int x0, int x1, int j) {
    int res = 0;
    for(int i = 0; i < n; i += 2) {
        if(get(i, j) != x0) res++;
    }
    for(int i = 1; i < n; i += 2) {
        if(get(i, j) != x1) res++;
    }
    return res;
}
bool row_;
int x0_, x1_;
int solve() {
    int ans = n * m;
    for(int x0 = 0; x0 < 4; x0++) for(int x1 = x0 + 1; x1 < 4; x1++) {
        int y0 = 0, y1 = 0;
        while(y0 == x0 || y0 == x1) y0++;
        while(y1 == y0 || y1 == x0 || y1 == x1) y1++;
        int cur = 0;
        for(int i = 0; i < n; i += 2) {
            cur += min(check_row(x0, x1, i), check_row(x1, x0, i));
        }
        for(int i = 1; i < n; i += 2) {
            cur += min(check_row(y0, y1, i), check_row(y1, y0, i));
        }
        if(cur < ans) {
            row_ = true;
            x0_ = x0; x1_ = x1;
            ans = cur;
        }
        cur = 0;
        for(int j = 0; j < m; j += 2) {
            cur += min(check_col(x0, x1, j), check_col(x1, x0, j));
        }
        for(int j = 1; j < m; j += 2) {
            cur += min(check_col(y0, y1, j), check_col(y1, y0, j));
        }
        if(cur < ans) {
            row_ = false;
            x0_ = x0; x1_ = x1;
            ans = cur;
        }
    }
    return ans;
}
char str[MAXN];
char pat[] = "AGCT";
int ans_board[MAXN];
int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;
    for(int i = 0; i < n; i++) {
        cin >> str;
        for(int j = 0; j < m; j++) {
            int cur;
            if(str[j] == 'A') cur = 0;
            else if(str[j] == 'G') cur = 1;
            else if(str[j] == 'C') cur = 2;
            else cur = 3;
            board[i * m + j] = cur;
        }
    }
    solve();
    int x0 = x0_, x1 = x1_;
    int y0 = 0, y1 = 0;
    while(y0 == x0 || y0 == x1) y0++;
    while(y1 == y0 || y1 == x0 || y1 == x1) y1++;
    if(row_) {
        for(int i = 0; i < n; i++) {
            int cur0, cur1;
            if(i & 1) cur0 = y0, cur1 = y1;
            else cur0 = x0, cur1 = x1;

            if(check_row(cur0, cur1, i) < check_row(cur1, cur0, i)) {
                for(int j = 0; j < m; j++) {
                    if(j & 1) ans_board[i * m + j] = cur1;
                    else ans_board[i * m + j] = cur0;
                }
            }
            else {
                for(int j = 0; j < m; j++) {
                    if(j & 1) ans_board[i * m + j] = cur0;
                    else ans_board[i * m + j] = cur1;
                }
            }
        }
    }
    else {
        for(int j = 0; j < m; j++) {
            int cur0, cur1;
            if(j & 1) cur0 = y0, cur1 = y1;
            else cur0 = x0, cur1 = x1;

            if(check_col(cur0, cur1, j) < check_col(cur1, cur0, j)) {
                for(int i = 0; i < n; i++) {
                    if(i & 1) ans_board[i * m + j] = cur1;
                    else ans_board[i * m + j] = cur0;
                }
            }
            else {
                for(int i = 0; i < n; i++) {
                    if(i & 1) ans_board[i * m + j] = cur0;
                    else ans_board[i * m + j] = cur1;
                }
            }
        }
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) cout << pat[ans_board[i * m + j]];
        cout << endl;
    }
    return 0;
}