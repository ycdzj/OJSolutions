#include <cstdio>

const int MAXN = 2005;
const int MOD = 1e9 + 7;
inline int addmod(int a, int b) {
    return (a + b) % MOD;
}

int n, m;
char board[MAXN][MAXN];
int val[MAXN][MAXN][2];
bool vis[MAXN][MAXN][2];

int cnt_row[MAXN][MAXN], cnt_col[MAXN][MAXN];
int g_row[MAXN][MAXN], g_col[MAXN][MAXN];
bool vis_g_row[MAXN][MAXN], vis_g_col[MAXN][MAXN];

int f(int, int, int);

int get_g_row(int i, int j) {
    if(i == n - 1) {
        return 0;
    }
    if(vis_g_row[i][j]) {
        return g_row[i][j];
    }
    int res = 0;

    int cnt = m - j - cnt_row[i][j];
    if(cnt > 0) {
        if(j == m - 1) {
            res = f(i + 1, j, 0);
        }
        else {
            res = addmod(get_g_row(i, j + 1), f(i + 1, j, 0));
            if(board[i][j] == 'R') {
                res = addmod(res, MOD - f(i + 1, j + cnt, 0));
            }
        }
    }
    vis_g_row[i][j] = true;
    return g_row[i][j] = res;
}
int get_g_col(int i, int j) {
    if(j == m - 1) {
        return 0;
    }
    if(vis_g_col[i][j]) {
        return g_col[i][j];
    }
    int res = 0;

    int cnt = n - i - cnt_col[i][j];
    if(cnt > 0) {
        if(i == n - 1) {
            res = f(i, j + 1, 1);
        }
        else {
            res = addmod(get_g_col(i + 1, j), f(i, j + 1, 1));
            if(board[i][j] == 'R') {
                res = addmod(res, MOD - f(i + cnt, j + 1, 1));
            }
        }
    }

    vis_g_col[i][j] = true;
    return g_col[i][j] = res;
}

int f(int i, int j, int k) {
    if(i >= n || j >= m) {
        return 0;
    }
    if(vis[i][j][k]) {
        return val[i][j][k];
    }
    int res = 0;
    if(i == n - 1 && j == m - 1) {
        if(board[i][j] == '.') {
            res = 1;
        }
    }
    else {
        if(board[i][j] == '.') {
            res = addmod(res, f(i + 1, j, 0));
            res = addmod(res, f(i, j + 1, 1));
        }
        else {
            if(k == 0) {
                res = get_g_col(i, j);
            }
            else {
                res = get_g_row(i, j);
            }
        }
    }

    vis[i][j][k] = true;
    return val[i][j][k] = res;
}

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 0; i < n; i++) {
        scanf("%s", board[i]);
    }
    for(int i = 0; i < n; i++) {
        for(int j = m - 1; j >= 0; j--) {
            cnt_row[i][j] = cnt_row[i][j + 1];
            if(board[i][j] == 'R') {
                cnt_row[i][j]++;
            }
        }
    }
    for(int j = 0; j < m; j++) {
        for(int i = n - 1; i >= 0; i--) {
            cnt_col[i][j] = cnt_col[i + 1][j];
            if(board[i][j] == 'R') {
                cnt_col[i][j]++;
            }
        }
    }
    printf("%d\n", f(0, 0, 0));
    return 0;
}
