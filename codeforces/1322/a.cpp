#include <iostream>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    int n;
    string str;
    cin >> n >> str;
    int ans = 0, cur = 0;
    for(int i = 0; i < str.length(); i++) {
        if(str[i] == '(') {
            cur++;
        } else {
            cur--;
        }
        if(cur < 0 || (cur == 0 && str[i] == '(')) {
            ans++;
        }
    }
    if(cur != 0) {
        ans = -1;
    }
    cout << ans << endl;
    return 0;
}




