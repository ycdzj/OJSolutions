#include <cstdio>
#include <vector>
#include <string>

using namespace std;

const int MAXN = 1e5 + 5;
char str[MAXN];

string solve(vector<int> cnt, int k) {
    for(int i = 0; i < 26; i++) {
        if(cnt[i] > 0) {
            if(cnt[i] < k) {
                for(int cur = 0, j = 0; j < 26; j++) {
                    cur += cnt[j];
                    if(cur >= k) {
                        string ans;
                        ans.push_back('a' + j);
                        return ans;
                    }
                }
            } else {
                string ans;
                ans.push_back('a' + i);
                cnt[i] -= k;
                int total = 0;
                for(int j = 0; j < 26; j++) {
                    if(cnt[j] > 0) {
                        total++;
                    }
                }
                if(total <= 1) {
                    for(int j = 0; j < 26; j++) {
                        if(cnt[j] > 0) {
                            int cur = (cnt[j] - 1) / k + 1;
                            while(cur-- > 0) {
                                ans.push_back('a' + j);
                            }
                        }
                    }
                } else {
                    for(int j = 0; j < 26; j++) {
                        while(cnt[j]-- > 0) {
                            ans.push_back('a' + j);
                        }
                    }
                }
                return ans;
            }
        }
    }
}

int main() {
    int t;
    scanf("%d", &t);
    while(t-- > 0) {
        int n, k;
        scanf("%d%d", &n, &k);
        scanf("%s", str);
        vector<int> cnt(26);
        for(int i = 0; i < n; i++) {
            cnt[str[i] - 'a']++;
        }
        printf("%s\n", solve(cnt, k).c_str());
    }
    return 0;
}
