    #include <cstdio>
    #include <algorithm>
    using namespace std;
     
    int board[15][15];
     
    void get_next(int i, int j, int &res_i, int &res_j, int k) {
        if(k == 0) {
            res_i = i;
            res_j = j;
            return;
        }
        if(i == 1 && j == 1) {
            res_i = -1;
            res_j = -1;
            return;
        }
        if((10 - i) & 1) {
            if(j > 1) {
                get_next(i, j - 1, res_i, res_j, k - 1);
            }
            else {
                get_next(i - 1, j, res_i, res_j, k - 1);
            }
        }
        else {
            if(j < 10) {
                get_next(i, j + 1, res_i, res_j, k - 1);
            }
            else {
                get_next(i - 1, j, res_i, res_j, k - 1);
            }
        }
    }
     
    double f[15][15];
    void calc(int i, int j) {
        if(i == 1 && j == 1) {
            return;
        }
        int cnt = 0;
        double cur = 0;
        for(int k = 1; k <= 6; k++) {
            int nxt_i, nxt_j;
            get_next(i, j, nxt_i, nxt_j, k);
            if(nxt_i == -1) {
                cnt++;
            }
            else {
                cur += min(f[nxt_i][nxt_j], f[nxt_i - board[nxt_i][nxt_j]][nxt_j]);
            }
        }
        f[i][j] = (6 + cur) / (6 - cnt);
    }
    int main() {
        for(int i = 1; i <= 10; i++) {
            for(int j = 1; j <= 10; j++) {
                scanf("%d", &board[i][j]);
            }
        }
        for(int i = 1; i <= 10; i++) {
            if((10 - i) & 1) {
                for(int j = 1; j <= 10; j++) {
                    calc(i, j);
                }
            }
            else {
                for(int j = 10; j >= 1; j--) {
                    calc(i, j);
                }
            }
        }
        printf("%.8f\n", f[10][1]);
        return 0;
    }
