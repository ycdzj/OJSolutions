#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

bool update(string &common_prefix, const string &name) {
    int len = 0;
    while(len < common_prefix.length() && len < name.length() && common_prefix[len] == name[len]) {
        len++;
    }
    if(len < common_prefix.length() && len < name.length()) {
        return false;
    }
    if(len == common_prefix.length()) {
        common_prefix = name;
    }
    return true;
}

string solve() {
    int n;
    cin >> n;
    vector<string> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    string common_prefix;
    for(int i = 0; i < n; i++) {
        int idx = a[i].find_first_of("*");
        if(idx == string::npos) {
            idx = a[i].length();
        }
        
        if(!update(common_prefix, a[i].substr(0, idx))) {
            return "*";
        }
    }
    string common_suffix;
    for(int i = 0; i < n; i++) {
        int idx = a[i].find_last_of("*");
        if(idx == string::npos) {
            idx = -1;
        }
        string suffix = a[i].substr(idx + 1, a[i].length() - idx - 1);
        reverse(suffix.begin(), suffix.end());
        if(!update(common_suffix, suffix)) {
            return "*";
        }
    }
    reverse(common_suffix.begin(), common_suffix.end());
    string ans;
    for(int i = 0; i < n; i++) {
        for(char c : a[i]) {
            if(c != '*') {
                ans.push_back(c);
            }
        }
    }
    return common_prefix + ans + common_suffix;
}

int main() {
    ios::sync_with_stdio(false);
    int t;
    cin >> t;
    for(int i = 1; i <= t; i++) {
        cout << "Case #" << i << ": " << solve() << endl;
    }
    return 0;
}