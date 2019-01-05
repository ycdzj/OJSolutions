#include <iostream>
using namespace std;

int main() {
    string t;
    cin >> t;
    bool ans = false;
    for(int i = 0; i < 5; i++) {
        string s;
        cin >> s;
        if(s[0] == t[0] || s[1] == t[1]) ans = true;
    }
    if(ans) cout << "YES" << endl;
    else cout << "NO" << endl;
    return 0;
}