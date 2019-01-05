#include <iostream>
using namespace std;

const int MAXN = 1e5 + 5;
long long l[MAXN];
char str[MAXN];
int n;

int main() {
    cin >> n;
    for(int i = 0; i < n; i++) cin >> l[i];
    cin >> str;

    bool water = false;
    long long f = 0;
    long long ans = 0;
    long long cur = 0;
    for(int i = 0; i < n; i++) {
        if(str[i] == 'L') {
            ans += l[i];
            cur -= l[i];
            if(cur < 0) {
                if(water) ans += 3 * -cur;
                else ans += 5 * -cur;
                cur = 0;
            }
        }
        else if(str[i] == 'G') {
            ans += 5 * l[i];
            cur += l[i];
            f += 2 * l[i];
        }
        else {
            water = true;
            ans += 3 * l[i];
            cur += l[i];
        }
        f = min(f, cur);
    }
    ans -= 2 * f;
    ans -= cur - f;

    cout << ans << endl;
    return 0;
}
