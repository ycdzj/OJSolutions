#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = (1 << 21) + 10;
char str[MAXN];
int len;

int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        scanf("%s", str);
        len = strlen(str);
        int bag = 1;
        vector<int> v;
        for(int i = 0; i < len; i++) {
            if(str[i] == '^') {
                v.push_back(bag);
                bag = 1;
            }
            else {
                bag++;
            }
        }
        v.push_back(bag);
        int ans = 0;
        sort(v.begin(), v.end());
        for(int i = v.size() - 1; i >= 0; i--) {
            int cur = v[i] / 2;
            for(int j = 25; j >= 0; j--) {
                if(cur >> j & 1) {
                    bool flag = false;
                    for(int k = j; k >= 0; k--) {
                        if(ans >> k & 1) {
                            if(cur >> k & 1) {
                                flag = true;
                            }
                        }
                        else {
                            if(flag || (cur >> k & 1)) {
                                ans = (ans | (1 << k));
                            }
                        }
                    }
                    break;
                }
            }
        }
        ans <<= 1;
        for(int i = 0; i < v.size(); i++) {
            if(v[i] & 1) {
                ans ^= 1;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}