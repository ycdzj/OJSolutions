#include <iostream>
using namespace std;

int main() {
    int t;
    cin >> t;
    while(t-- > 0) {
        int d, m;
        cin >> d >> m;
        d++;
        long long ans = 1;
        for(int i = 0; i < 30; i++) {
            int left = (1 << i);
            int right = min(1 << (i + 1), d);
            if(left < right) {
                ans = (ans * (right - left + 1)) % m;
            } else {
                break;
            }
        }
        ans = (ans + m - 1) % m;
        cout << ans << endl;
    }
    return 0;
}