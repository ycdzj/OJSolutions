#include <cstdio>
const int MAXN = 100;
int board[MAXN][MAXN];
bool check(int x, int y) {
    int l = x, r = x;
    int val = board[x][y];
    while(board[l - 1][y] == val) l--;
    while(board[r + 1][y] == val) r++;
    if(r - l + 1 >= 5) return true;
    l = y;
    r = y;
    while(board[x][l - 1] == val) l--;
    while(board[x][r + 1] == val) r++;
    if(r - l + 1 >= 5) return true;
    l = 0;
    r = 0;
    while(board[x + (l - 1)][y + (l - 1)] == val) l--;
    while(board[x + (r + 1)][y + (r + 1)] == val) r++;
    if(r - l + 1 >= 5) return true;
    l = 0;
    r = 0;
    while(board[x + (l - 1)][y - (l - 1)] == val) l--;
    while(board[x + (r + 1)][y - (r + 1)] == val) r++;
    if(r - l + 1 >= 5) return true;
    return false;
}
int main() {
    int n; scanf("%d", &n);
    int ans = 0;
    for(int i = 1; i <= n; i++) {
        int x, y; scanf("%d%d", &x, &y);
        board[x][y] = (i % 2 == 0 ? -1 : 1);
        if(ans == 0 && check(x, y)) {
            ans = i;
        }
    }
    if(ans == 0) printf("Tie\n");
    else if(ans % 2 == 0) printf("B %d\n", ans);
    else printf("A %d\n", ans);
    return 0;
}