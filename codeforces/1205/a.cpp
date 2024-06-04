#include <iostream>
#include <vector>
using namespace std;
int main() {
    int n;
    cin >> n;
    if(n & 1) {
        cout << "YES" << endl;
        vector<int> v(2 * n);
        for(int i = 0; i < n; i++) {
            int j = i + n;
            v[i] = i * 2 + 1;
            v[j] = i * 2 + 2;
            if(i & 1) {
                swap(v[i], v[j]);
            }
        }
        for(int i = 0; i < 2 * n; i++) {
            cout << v[i] << ' ';
        }
        cout << endl;
    }
    else {
        cout << "NO" << endl;
    }
    return 0;
}