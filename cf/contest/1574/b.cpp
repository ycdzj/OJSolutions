#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void solve() {
    int a, b, c, m;
    cin >> a >> b >> c >> m;

    vector<int> arr = {a, b, c};
    sort(arr.rbegin(), arr.rend());
    a = arr[0];
    b = arr[1];
    c = arr[2];

    int max_val = max(a - 1, 0) + max(b - 1, 0) + max(c - 1, 0);
    int min_val = max(a - 1 - b - c, 0);

    if(min_val <= m && m <= max_val) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
}

int main() {
    int t;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}