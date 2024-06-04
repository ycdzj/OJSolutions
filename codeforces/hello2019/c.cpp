#include <iostream>
#include <map>
using namespace std;

const int MAXN = 5e5 + 5;
map<int, int> cnt;
int n;
char str[MAXN];

int main() {
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> str;
        int cur = 0, min_ = 0;
        for(int j = 0; str[j] != '\0'; j++) {
            if(str[j] == '(') cur++;
            else if(str[j] == ')') cur--;
            min_ = min(min_, cur);
        }
        if((cur >= 0 && min_ >= 0) || (cur <= 0 && -cur + min_ >= 0)) cnt[cur]++;
    }
    int ans = 0;
    for(auto pr : cnt) if(pr.first > 0) {
        ans += min(pr.second, cnt[-pr.first]);
    }
    ans += cnt[0] / 2;
    cout << ans << endl;
    return 0;
}
