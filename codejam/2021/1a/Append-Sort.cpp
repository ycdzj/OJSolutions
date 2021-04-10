#include <iostream>
#include <string>
using namespace std;

string strip_zero(const string &s) {
    int i = 0;
    while(i < s.length() && s[i] == '0') {
        i++;
    }
    if(i == s.length()) {
        return "0";
    }
    return s.substr(i, s.length() - i);
}

void increase(string &s) {
    int bag = 1;
    for(int i = s.length() - 1; i >= 0; i--) {
        s[i] += bag;
        if(s[i] > '9') {
            s[i] -= 10;
            bag = 1;
        } else {
            bag = 0;
        }
    }
    if(bag == 1) {
        s.insert(0, "1");
    }
}

void solve(int i_case) {
    int n;
    cin >> n;
    string pre = "0";
    int ans = 0;
    for(int i = 0; i < n; i++) {
        string cur;
        cin >> cur;
        cur = strip_zero(cur);
        if(cur.length() <= pre.length()) {
            int cp = cur.compare(0, cur.length(), pre.c_str(), cur.length());
            if(cp == 0) {
                for(int j = cur.length(); j < pre.length(); j++) {
                    cur.push_back(pre[j]);
                    ans++;
                }
            } else if(cp < 0) {
                while(cur.length() < pre.length() + 1) {
                    cur.push_back('0');
                    ans++;
                }
            } else {
                while(cur.length() < pre.length()) {
                    cur.push_back('0');
                    ans++;
                }
            }
        }
        increase(cur);
        pre = cur;
    }
    cout << "Case #" << i_case << ": " << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    int t;
    cin >> t;
    for(int i_case = 1; i_case <= t; i_case++) {
        solve(i_case);
    }
    return 0;
}