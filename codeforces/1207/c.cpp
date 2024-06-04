#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 2e5 + 15;
const long long INF = 1e18;

long long f[MAXN][2];
int n, a, b;
char str[MAXN];

int main() {
    ios::sync_with_stdio(false);
    int T;
    cin >> T;
    while(T--) {
        cin >> n >> a >> b;
        cin >> str;
        f[n][0] = b;
        f[n][1] = INF;
        for(int i = n - 1; i >= 0; i--) {
            if(str[i] == '1') {
                f[i][0] = INF;
                f[i][1] = f[i + 1][1] + a + 2 * b;
            }
            else {
                f[i][0] = min(f[i + 1][0] + a + b, f[i + 1][1] + 2 * a + b);
                f[i][1] = min(f[i + 1][1] + a + 2 * b, f[i + 1][0] + 2 * a + 2 * b);
            }
        }
        cout << f[0][0] << endl;
    }

    return 0;
}
