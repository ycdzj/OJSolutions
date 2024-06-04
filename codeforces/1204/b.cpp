#include <iostream>
using namespace std;

int main() {
    int n, l, r;
    cin >> n >> l >> r;
    cout << (1 << l) - 1 + n - l << ' ' << (1 << r) - 1 + (long long)(1 << (r - 1)) * (n - r) << endl;
    return 0;
}
