#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

bool is_prime(int x) {
    for(int i = 2; i * i <= x; i++) {
        if(x % i == 0) {
            return false;
        }
    }
    return true;
}

void solve() {
    int n;
    cin >> n;

    vector<int> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }

    int s = accumulate(a.begin(), a.end(), 0);

    if(!is_prime(s)) {
        cout << n << endl;
        for(int i = 1; i <= n; i++) {
            cout << i << ' ';
        }
        cout << endl;
        return;
    }
    
    cout << n - 1 << endl;
    bool flag = false;
    for(int i = 0; i < n; i++) {
        if(a[i] % 2 == 1) {
            if(!flag) {
                flag = true;
                continue;
            }
        }
        cout << i + 1 << ' ';
    }
    cout << endl;
}

int main() {
    int t;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}