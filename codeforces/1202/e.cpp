#include <iostream>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;

const int MAXN = 2e5 + 5;

struct ACA {
    struct Node {
        int next[26], fail, end, cnt;
        void init() {
            memset(next, 0, sizeof(next));
            fail = 0;
            end = 0;
            cnt = 0;
        }
    } t[MAXN];
    int cnt_node;
    int new_node() {
        t[cnt_node].init();
        return cnt_node++;
    }

    int root;
    void init() {
        cnt_node = 1;
        root = new_node();
    }
    void insert(const char *str, int len) {
        int cur = root;
        for(int i = 0; i < len; i++) {
            int ch = str[i] - 'a';
            if(t[cur].next[ch] == 0) {
                t[cur].next[ch] = new_node();
            }
            cur = t[cur].next[ch];
        }
        t[cur].end++;
    }
    void build() {
        queue<int> que;
        t[root].fail = root;
        for(int i = 0; i < 26; i++) {
            if(t[root].next[i] == 0) {
                t[root].next[i] = root;
            }
            else {
                t[t[root].next[i]].fail = root;
                que.push(t[root].next[i]);
            }
        }
        while(!que.empty()) {
            int u = que.front();
            que.pop();
            t[u].end += t[t[u].fail].end;
            for(int i = 0; i < 26; i++) {
                if(t[u].next[i] == 0) {
                    t[u].next[i] = t[t[u].fail].next[i];
                }
                else {
                    t[t[u].next[i]].fail = t[t[u].fail].next[i];
                    que.push(t[u].next[i]);
                }
            }
        }
    }
} aca;

int main() {
    ios::sync_with_stdio(false);
    string t;
    vector<string> v;
    vector<int> cnt;
    int n;

    cin >> t >> n;
    int len = t.length();
    v.resize(n);
    cnt.resize(len);
    aca.init();
    for(int i = 0; i < n; i++) {
        cin >> v[i];
        aca.insert(v[i].c_str(), v[i].length());
    }

    aca.build();
    for(int cur = aca.root, i = 0; i < len; i++) {
        cur = aca.t[cur].next[t[i] - 'a'];
        cnt[i] = aca.t[cur].end;
    }

    long long ans = 0;
    aca.init();
    for(int i = 0; i < n; i++) {
        reverse(v[i].begin(), v[i].end());
        aca.insert(v[i].c_str(), v[i].length());
    }

    aca.build();
    for(int cur = aca.root, i = len - 1; i >= 1; i--) {
        cur = aca.t[cur].next[t[i] - 'a'];
        ans += (long long)cnt[i - 1] * aca.t[cur].end;
    }

    cout << ans << endl;
    return 0;
}
