#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 55;

int a[MAXN][MAXN], b[MAXN][MAXN], n, m;
vector<pair<int, int>> op;

int main() {
    cin >> n >> m;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            cin >> a[i][j];
        }
    }
    for(int i = 1; i < n; i++) {
        for(int j = 1; j < m; j++) {
            if(a[i][j] == 1 && a[i + 1][j] == 1 && a[i][j + 1] == 1 && a[i + 1][j + 1] == 1) {
                b[i][j] = 1;
                b[i + 1][j] = 1;
                b[i][j + 1] = 1;
                b[i + 1][j + 1] = 1;
                op.push_back({i, j});
            }
        }
    }
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            if(a[i][j] != b[i][j]) {
                cout << "-1" << endl;
                return 0;
            }
        }
    }
    cout << op.size() << endl;
    for(auto pr : op) {
        cout << pr.first << ' ' << pr.second << endl;
    }
    return 0;
}
