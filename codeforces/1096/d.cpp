#include <iostream>
using namespace std;

const int MAXN = 1e5 + 5;
int n;
char str[MAXN], pat[] = " hard";
int a[MAXN];
long long f[MAXN][4];

int main() {
    cin >> n >> str + 1;
    for(int i = 1; i <= n; i++) cin >> a[i];

    for(int i = 1; i <= n; i++) for(int j = 0; j <= 3; j++) {
        f[i][j] = f[i - 1][j];
        if(str[i] == pat[j + 1]) f[i][j] += a[i];
        if(j >= 1) f[i][j] = std::min(f[i][j], f[i - 1][j - 1]);
    }

    cout << f[n][3] << endl;
    return 0;
}
