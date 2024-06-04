#include <cstdio>
#include <cstring>
#include <queue>
const int MAXN = 1e6 + 5;
struct ACA {
    struct Node {
        int next[26], fail;
        int end, vis;
    } t[MAXN];
    int cnt_node;
    int new_node() {
        memset(&t[cnt_node], 0, sizeof(Node));
        return cnt_node++;
    }

    int root;
    void init() {
        cnt_node = 1;
        root = new_node();
    }
    void insert(char *str, int len) {
        int cur = root;
        for(int i = 0; i < len; i++) {
            if(t[cur].next[str[i] - 'a'] == 0) {
                t[cur].next[str[i] - 'a'] = new_node();
            }
            cur = t[cur].next[str[i] - 'a'];
        }
        t[cur].end++;
    }
    void build() {
        std::queue<int> que;
        t[root].fail = root;
        for(int i = 0; i < 26; i++) {
            if(t[root].next[i] == 0) t[root].next[i] = root;
            else {
                t[t[root].next[i]].fail = root;
                que.push(t[root].next[i]);
            }
        }
        while(!que.empty()) {
            int u = que.front(); que.pop();
            for(int i = 0; i < 26; i++) {
                if(t[u].next[i] == 0) t[u].next[i] = t[t[u].fail].next[i];
                else {
                    t[t[u].next[i]].fail = t[t[u].fail].next[i];
                    que.push(t[u].next[i]);
                }
            }
        }
    }
    int query(char *str, int len) {
        int res = 0;
        int cur = root;
        for(int i = 0; i < len; i++) {
            if(t[cur].next[str[i] - 'a'] == 0) break;
            cur = t[cur].next[str[i] - 'a'];
            for(int u = cur; t[u].vis == 0; u = t[u].fail) {
                res += t[u].end;
                t[u].vis = 1;
            }
        }
        return res;
    }
} ac;
char str[MAXN];
int main() {
    ac.init();
    int n; scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        scanf("%s", str);
        ac.insert(str, strlen(str));
    }
    ac.build();
    scanf("%s", str);
    printf("%d\n", ac.query(str, strlen(str)));
    return 0;
}
