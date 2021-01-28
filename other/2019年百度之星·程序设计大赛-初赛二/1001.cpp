#include <iostream>
#include <vector>
using namespace std;

int main() {
    int T;
    cin >> T;
    while(T--) {
        int v;
        cin >> v;
        int sum = 0;
        for(int x = v; x != 0; x /= 10) {
            sum += x % 10;
        }
        vector<int> ans;
        for(int x = 1; x <= sum; x++) {
            if(sum % x == 0 && v % x == 0) {
                ans.push_back(x);
            }
        }
        cout << ans.size() << endl;
        for(int i = 0; i < ans.size(); i++) {
            cout << ans[i];
            if(i + 1 < ans.size()) {
                cout << ' ';
            }
            else {
                cout << endl;
            }
        }
    }
    return 0;
}
