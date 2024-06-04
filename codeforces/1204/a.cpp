#include <iostream>
using namespace std;


int main() {
    string str;
    cin >> str;
    if(str.length() == 1) {
        cout << 0 << endl;
        return 0;
    }
    int len = str.length() - 1;
    for(int i = 1; i < str.length(); i++) {
        if(str[i] == '1') {
            len++;
            break;
        }
    }
    cout << (len - 1) / 2 + 1<< endl;
    return 0;
}
