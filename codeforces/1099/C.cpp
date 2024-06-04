#include <iostream>
using namespace std;
string str;
int k;
int main() {
    cin >> str >> k;
    int len = str.length();
    int cnt_1 = 0, cnt_2 = 0;
    for(int i = 0; i < len; i++) {
        if(str[i] == '?') cnt_1++;
        if(str[i] == '*') cnt_2++;
    }
    int min_ = len - cnt_1 * 2 - cnt_2 * 2;
    if(min_ > k) cout << "Impossible" << endl;
    else {
        int x = k - min_;
        if(cnt_2 > 0) {
            for(int i = 0; i < len; i++) {
                if(str[i] != '*' && str[i] != '?' && ((i + 1 < len && str[i + 1] != '*' && str[i + 1] != '?') || i + 1 == len))
                    cout << str[i];
                else if(str[i] == '*') {
                    while(x > 0) {
                        cout << str[i - 1];
                        x--;
                    }
                }
            }
            cout << endl;
        }
        else if(min_ + cnt_1 >= k) {
            for(int i = 0; i < len; i++) {
                if(str[i] != '*' && str[i] != '?' && ((i + 1 < len && str[i + 1] != '*' && str[i + 1] != '?') || i + 1 == len))
                    cout << str[i];
                else if(str[i] == '?') {
                    if(x > 0) {
                        cout << str[i - 1];
                        x--;
                    }
                }
            }
            cout << endl;
        }
        else {
            cout << "Impossible" << endl;
        }
    }
    return 0;
}