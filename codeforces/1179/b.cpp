#include <cstdio>

void print(int i, int j) {
    printf("%d %d\n", i, j);
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    for(int j = 1; j <= m + 1 - j; j++) {
        if(j < m + 1 - j) {
            int cur_i = 1, cur_j = j;
            while(true) {
                print(cur_i, cur_j);
                if(cur_j == j) {
                    cur_i = n + 1 - cur_i;
                    cur_j = m + 1 - j;
                }
                else {
                    if(cur_i == 1) {
                        break;
                    }
                    else {
                        cur_i = n + 2 - cur_i;
                        cur_j = j;
                    }
                }
            }
        }
        else {
            for(int i = 1; i <= n + 1 - i; i++) {
                print(i, j);
                if(i < n + 1 - i) {
                    print(n + 1 - i, j);
                }
            }
        }
    }
    return 0;
}
