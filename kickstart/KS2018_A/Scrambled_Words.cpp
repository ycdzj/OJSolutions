#include <cstdio>
#include <cstring>
#include <algorithm>
#include <unordered_map>
using namespace std;

const int MAXN = 1e6 + 5;
const int MOD = 1e9 + 7;
const int STEP = 37;
typedef long long ll;

inline int addmod(int a, int b) { return (a + b) % MOD; }
inline int mulmod(ll a, int b) { return (a * b) % MOD; }

int l, n;
ll a, b, c, d;
char str[MAXN];
unordered_map<int, int> vis[26][26];
int cnt[26];

struct Item {
    int val, len;
    char s, t;
} item[MAXN];
bool cmp(Item a, Item b) {
    return a.len < b.len;
}

void build(int l, int r) {
    for(int i = 0; i < 26; i++) for(int j = 0; j < 26; j++) {
        vis[i][j].clear();
    }
    for(int i = l; i < r; i++) {
        vis[item[i].s - 'a'][item[i].t - 'a'][item[i].val]++;
    }
}
int po[26];
int main() {
    int T;
    scanf("%d", &T);
    po[0] = 1;
    for(int i = 1; i < 26; i++) po[i] = mulmod(po[i - 1], STEP);
    for(int cnt_case = 1; cnt_case <= T; cnt_case++) {
        scanf("%d", &l);
        for(int i = 0; i < l; i++) {
            scanf("%s", str);
            int len = strlen(str);
            memset(cnt, 0, sizeof(cnt));
            for(int j = 1; j < len - 1; j++) cnt[str[j] - 'a']++;
            int cur = 0;
            for(int j = 0; j < 26; j++) cur = addmod(mulmod(cur, STEP), cnt[j]);
            item[i] = { cur, len, str[0], str[len - 1] };
        }
        scanf("%s", str);
        scanf("%s", str + 1);
        scanf("%d%lld%lld%lld%lld", &n, &a, &b, &c, &d);
        ll x[3] = { str[0], str[1], 0 };
        for(int i = 2; i < n; i++) {
            x[i % 3] = (a * x[(i - 1) % 3] + b * x[(i - 2) % 3] + c) % d;
            str[i] = 'a' + (char)(x[i % 3] % 26);
        }
        sort(item, item + l, cmp);
        int ans = 0;
        for(int i = 0; i < l; ) {
            int nxt_i = i;
            while(nxt_i < l && item[nxt_i].len == item[i].len) nxt_i++;
            build(i, nxt_i);
            int len = item[i].len;
            int val = 0, l = 0, r = 0;
            for(int s = 0; s + len <= n; s++) {
                //[s + 1, s + len - 1)
                for(; r < s + len - 1; r++) val = addmod(val, po[25 - (str[r] - 'a')]);
                for(; l < s + 1; l++) val = addmod(val, MOD - po[25 - (str[l] - 'a')]);
                auto itr = vis[str[s] - 'a'][str[s + len - 1] - 'a'].find(val);
                if(itr != vis[str[s] - 'a'][str[s + len - 1] - 'a'].end()) {
                    ans += itr->second;
                    itr->second = 0;
                }
            }
            i = nxt_i;
        }
        printf("Case #%d: %d\n", cnt_case, ans);
    }
    return 0;
}
