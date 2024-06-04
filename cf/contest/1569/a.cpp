#include <iostream>
using namespace std;

void solve() {
    int n;
    string str;
    cin >> n >> str;
    for(int i = 0; i + 1 < n; i++) {
        if(str[i] != str[i + 1]) {
            cout << i + 1 << ' ' << i + 2 << endl;
            return;
        }
    }
    cout << -1 << ' ' << -1 << endl;
}

int main() {
    int t;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}