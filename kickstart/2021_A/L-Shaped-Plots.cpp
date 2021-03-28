#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN = 1005;

int r, c;
int board[MAXN][MAXN];
int up[MAXN][MAXN], left[MAXN][MAXN], right[MAXN][MAXN], down[MAXN][MAXN];

int solve(int a, int b) {
    return max(0, min(a, b / 2) - 1);
}
int solve(int u, int l, int r, int d) {
    int ans = 0;
    ans += solve(u, l) + solve(u, r);
    ans += solve(l, u) + solve(l, d);
    ans += solve(r, u) + solve(r, d);
    ans += solve(d, l) + solve(d, r);
    return ans;
}

int main() {
    int t;
    scanf("%d", &t);
    for(int i_case = 1; i_case <= t; i_case++) {
        scanf("%d%d", &r, &c);
        for(int i = 1; i <= r; i++) {
            for(int j = 1; j <= c; j++) {
                scanf("%d", &board[i][j]);
                up[i][j] = up[i - 1][j];
                left[i][j] = left[i][j - 1];
                if(board[i][j] == 0) {
                    up[i][j] = i;
                    left[i][j] = j;
                }
            }
        }
        for(int i = 1; i <= r; i++) {
            right[i][c + 1] = c + 1;
        }
        for(int j = 1; j <= c; j++) {
            down[r + 1][j] = r + 1;
        }
        
        long long ans = 0;
        for(int i = r; i >= 1; i--) {
            for(int j = c; j >= 1; j--) {
                right[i][j] = right[i][j + 1];
                down[i][j] = down[i + 1][j];
                if(board[i][j] == 0) {
                    right[i][j] = j;
                    down[i][j] = i;
                }
                ans += solve(i - up[i][j], j - left[i][j], right[i][j] - j, down[i][j] - i);
            }
        }

        printf("Case #%d: %lld\n", i_case, ans);
    }
    return 0;
}