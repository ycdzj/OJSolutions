#include <cstdio>
int mat[4][4] = {
    {8, 9, 1, 13},
    {3, 12, 7, 5},
    {0, 2, 4, 11},
    {6, 10, 15, 14}
};
int main() {
    int n;
    scanf("%d", &n);
    int m = n / 4;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            int x = i % m;
            int y = j % m;
            int val = m * x + y;
            printf("%d ", (val << 4) + mat[i / m][j / m]);
        }
        printf("\n");
    }
    return 0;
}
