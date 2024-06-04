#include <iostream>
#include <vector>
using namespace std;

int main() {
    string str;
    cin >> str;
    int len = str.length();
    vector<bool> vis(str.length());
    for(int r = len - 1; r >= 0; r--) {
        int f = 0, cnt = 0;
        for(int l = r; l >= 0; l--) {
            if(str[l] == '0') {
                f++;
            }
            else {
                cnt++;
                f = max(f, cnt);
            }
            if(f != cnt) {
                vis[l] = true;
            }
        }
    }
    for(int i = 0; i < len; i++) {
        if(str[i] == '0' || i == len - 1 || !vis[i + 1]) {
            cout << '0';
        }
        else {
            cout << '1';
        }
    }
    cout << endl;
    return 0;
}
