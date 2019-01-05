#include <iostream>
using namespace std;
int deg[100];
int n;
int main() {
    cin >> n;
    for(int i = 0; i < n; i++) cin >> deg[i];
    bool ans = false;
    for(int mask = 0; mask < (1 << n); mask++) {
        int cur = 0;
        for(int i = 0; i < n; i++) {
            if(mask >> i & 1) cur += deg[i];
            else cur -= deg[i];
        }
        if(cur % 360 == 0) {
            ans = true;
            break;
        }
    }
    if(ans) cout << "YES" << endl;
    else cout << "NO" << endl;
    return 0;
}
