#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
using namespace std;
const int MAXN = 1e5 + 5;
const int MOD[2] = {(int)1e9 + 7, (int)1e9 + 9};
const int STEP[2] = {197, 199};
inline int addmod(int a, int b, int j) { return (a + b) % MOD[j]; }
inline int mulmod(long long a, int b, int j) { return (a * b) % MOD[j]; }
int n, m;
char *str[MAXN], buf[MAXN * 2], s[MAXN];
int len[MAXN], lenbuf[MAXN], len_s;
int ans[MAXN];
int hash_[MAXN][2], pow[MAXN][2];
void solve(int cur) {
    map<pair<int, int>, pair<int, int>> pre;
    for(int i = cur - 1; i < len_s; i++) {
        int val[2] = { hash_[i][0], hash_[i][1] };
        if(i - cur >= 0) {
            for(int j = 0; j < 2; j++) {
                val[j] = addmod(val[j], MOD[j] - mulmod(hash_[i - cur][j], pow[cur][j], j), j);
            }
        }
        pair<int, int> pr = { val[0], val[1] };
        auto itr = pre.find(pr);
        if(itr == pre.end()) pre[pr] = {i, 1};
        else if(i - itr->second.first >= cur) {
            itr->second.first = i;
            itr->second.second++;
        }
    }
    for(int i = 0; i < m; i++) if(len[i] == cur) {
        int cur_hash[2] = {0, 0};
        for(int j = 0; j < len[i]; j++) {
            for(int k = 0; k < 2; k++) {
                cur_hash[k] = addmod(str[i][j], mulmod(cur_hash[k], STEP[k], k), k);
            }
        }
        ans[i] = pre[{cur_hash[0], cur_hash[1]}].second;
    }
}
int main() {
    scanf("%d%d", &n, &m);
    scanf("%s", s);
    int left = 0;
    for(int i = 0; i < m; i++) {
        str[i] = &buf[left];
        scanf("%s", str[i]);
        len[i] = lenbuf[i] = strlen(str[i]);
        left += len[i] + 1;
    }
    sort(lenbuf, lenbuf + m);
    int cnt = unique(lenbuf, lenbuf + m) - lenbuf;
    len_s = strlen(s);
    pow[0][0] = pow[0][1] = 1;
    for(int i = 1; i < len_s; i++) {
        pow[i][0] = mulmod(pow[i - 1][0], STEP[0], 0);
        pow[i][1] = mulmod(pow[i - 1][1], STEP[1], 1);
    }
    for(int i = 0; i < len_s; i++) {
        for(int j = 0; j < 2; j++) {
            hash_[i][j] = s[i];
            if(i > 0) hash_[i][j] = addmod(hash_[i][j], mulmod(hash_[i - 1][j], STEP[j], j), j);
        }
    }
    for(int i = 0; i < cnt; i++) solve(lenbuf[i]);
    for(int i = 0; i < m; i++) printf("%d\n", ans[i]);
    return 0;
}
