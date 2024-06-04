#include <algorithm>
#include <cstdio>
#include <cstring>
#include <numeric>
#include <vector>
using namespace std;

const int MAXN = 85;

int f[MAXN][MAXN * 2][MAXN * MAXN];

inline int abs(int x) {
    if (x > 0) {
        return x;
    }
    return -x;
}

int main() {
    int n;
    scanf("%d", &n);

    vector<int> a;
    for (int i = 0; i < n; i++) {
        int val;
        scanf("%d", &val);
        a.push_back(val);
    }
    a.push_back(1);

    vector<int> b;
    for (int i = 0, pre = -1; i <= n; i++) {
        if (a[i] == 1) {
            b.push_back(i - pre - 1);
            pre = i;
        }
    }
    int m = b.size();
    int sum = accumulate(b.begin(), b.end(), 0);

    memset(f, 0x3f, sizeof(f));
    memset(f[0][sum], 0, sizeof(f[0][sum]));

    int max_j = n * (n - 1) / 2;

    for (int i = 1; i <= m; i++) {
        for (int x = -sum; x <= sum; x++) {
            for (int j = 0; j <= max_j; j++) {
                int max_y = min(j, sum);
                for (int y = -max_y; y <= max_y; y++) {
                    int val = b[i - 1] - x + y;
                    if (val < 0) {
                        continue;
                    }
                    f[i][x + sum][j] = min(f[i][x + sum][j], f[i - 1][y + sum][j - abs(y)] + val * val);
                }
            }
        }
    }

    for (int j = 0; j <= max_j; j++) {
        printf("%d\n", (sum * sum - f[m][sum][j]) / 2);
    }
    return 0;
}
