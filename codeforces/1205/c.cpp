#include <cstdio>

const int MAXN = 55;

int board[MAXN][MAXN];
int n;

bool ask(int x1, int y1, int x2, int y2) {
    printf("? %d %d %d %d\n", x1, y1, x2, y2);
    fflush(stdout);
    int res;
    scanf("%d", &res);
    return res == 1;
}

int seq[4], cnt_seq;
bool dfs(int i, int j, int &nxt_i, int &nxt_j) {
    if(i > n || j > n) {
        return false;
    }
    seq[cnt_seq++] = board[i][j];
    if(cnt_seq == 4) {
        if((seq[0] == seq[2]) == (seq[1] == seq[3])) {
            nxt_i = i;
            nxt_j = j;
            return true;
        }
        else {
            cnt_seq--;
            return false;
        }
    }
    if(dfs(i + 1, j, nxt_i, nxt_j) || dfs(i, j + 1, nxt_i, nxt_j)) {
        return true;
    }
    else {
        cnt_seq--;
        return false;
    }
}

int main() {
    scanf("%d", &n);
    board[1][1] = 1;
    board[n][n] = 0;
    board[1][2] = 0;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            if((i == 1 && j == 1) || (i == n && j == n) || (i == 1 && j == 2)) {
                continue;
            }
            int x[3] = {i - 2, i - 1, i};
            int y[3] = {j, j - 1, j - 2};
            for(int k = 0; k < 3; k++) {
                if(1 <= x[k] && 1 <= y[k]) {
                    board[i][j] = ask(x[k], y[k], i, j) == board[x[k]][y[k]];
                    break;
                }
            }
        }
        if(i == 2) {
            board[2][1] = ask(2, 1, 2, 3) == board[2][3];
        }
    }
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            int nxt_i, nxt_j;
            if(dfs(i, j, nxt_i, nxt_j)) {
                bool rev = false;
                if(ask(i, j, nxt_i, nxt_j) != (board[i][j] == board[nxt_i][nxt_j])) {
                    rev = true;
                }
                printf("!\n");
                for(int x = 1; x <= n; x++) {
                    for(int y = 1; y <= n; y++) {
                        if(rev && (x + y) % 2 == 1) {
                            board[x][y] = !board[x][y];
                        }
                        putchar(board[x][y] ? '1' : '0');
                    }
                    putchar('\n');
                }
                return 0;
            }
        }
    }
    return 0;
}
