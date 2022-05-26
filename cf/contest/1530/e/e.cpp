#include <iostream>
#include <string>
#include <vector>
using namespace std;

void solve() {
    string s;
    cin >> s;

    vector<int> cnt(26);
    for(int i = 0; i < s.length(); i++) {
        cnt[s[i] - 'a']++;
    }

    for(int i = 0; i < 26; i++) {
        if(cnt[i] == 1) {
            cout << (char)('a' + i);
            cnt[i]--;
            for(int j = 0; j < 26; j++) {
                while(cnt[j] > 0) {
                    cout << (char)('a' + j);
                    cnt[j]--;
                }
            }
            cout << endl;
            return;
        }
    }

    int first = 0;
    while(cnt[first] == 0) {
        first++;
    }

    if(cnt[first] == 1) {
        for(int i = first; i < 26; i++) {
            while(cnt[i] > 0) {
                cout << (char)('a' + i);
                cnt[i]--;
            }
        }
        cout << endl;
        return;
    }

    if(cnt[first] < s.length() && cnt[first] - 2 <= s.length() - cnt[first]) {
        cout << (char)('a' + first);
        cout << (char)('a' + first);
        cnt[first] -= 2;
        for(int i = first + 1; i < 26; i++) {
            while(cnt[i] > 0) {
                cout << (char)('a' + i);
                cnt[i]--;
                if(cnt[first] > 0) {
                    cout << (char)('a' + first);
                    cnt[first]--;
                }
            }
        }
        cout << endl;
        return;
    }

    int ch_cnt = 0;
    for(int i = 0; i < 26; i++) {
        if(cnt[i] > 0) {
            ch_cnt++;
        }
    }

    if(ch_cnt == 1) {
        for(int i = first; i < 26; i++) {
            while(cnt[i] > 0) {
                cout << (char)('a' + i);
                cnt[i]--;
            }
        }
        cout << endl;
        return;
    }

    int second = first + 1;
    while(cnt[second] == 0) {
        second++;
    }

    if(ch_cnt == 2) {
        cout << (char)('a' + first);
        cnt[first]--;

        while(cnt[second] > 0) {
            cout << (char)('a' + second);
            cnt[second]--;
        }

        while(cnt[first] > 0) {
            cout << (char)('a' + first);
            cnt[first]--;
        }

        cout << endl;
        return;
    }

    int third = second + 1;
    while(cnt[third] == 0) {
        third++;
    }

    cout << (char)('a' + first);
    cnt[first]--;
    cout << (char)('a' + second);
    cnt[second]--;

    while(cnt[first] > 0) {
        cout << (char)('a' + first);
        cnt[first]--;
    }

    cout << (char)('a' + third);
    cnt[third]--;

    for(int i = first; i < 26; i++) {
        while(cnt[i] > 0) {
            cout << (char)('a' + i);
            cnt[i]--;
        }
    }
    cout << endl;
}

int main() {
    ios::sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}

