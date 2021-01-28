#include <cstdio>
#include <queue>
#include <vector>
using namespace std;
const int MAXN = 2e5 + 5;
struct Node {
    int l, r, lc, rc;
} node[MAXN];
int ans[MAXN], cnt_ans;
void print(int u) {
    if(node[u].lc == -1 || node[u].rc == -1) {
        return;
    }
    ans[cnt_ans++] = node[node[u].lc].r;
    print(node[u].lc);
    print(node[u].rc);
}
vector<int> v[MAXN], fin[MAXN];
int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        int n;
        scanf("%d", &n);
        for(int i = 0; i <= n; i++) {
            v[i].clear();
            fin[i].clear();
        }
        for(int i = 0; i < n; i++) {
            int a;
            scanf("%d", &a);
            node[i] = {i + 1, i + 1, -1, -1};
            v[a].push_back(i);
        }
        int cnt_node = n;
        bool flag = false;
        for(int i = n; i >= 1; i--) {
            if(fin[i].size() % 2 == 1) {
                flag = true;
                break;
            }
            int i1 = 0, i2 = 0;
            while(i1 < fin[i].size() || i2 < v[i - 1].size()) {
                if(i1 == fin[i].size() || (i2 < v[i - 1].size() && node[v[i - 1][i2]].l < node[fin[i][i1]].l)) {
                    fin[i - 1].push_back(v[i - 1][i2]);
                    i2++;
                }
                else {
                    if(i1 + 1 < fin[i].size() && node[fin[i][i1]].r + 1 == node[fin[i][i1 + 1]].l) {
                        node[cnt_node] = {node[fin[i][i1]].l, node[fin[i][i1 + 1]].r, fin[i][i1], fin[i][i1 + 1]};
                        fin[i - 1].push_back(cnt_node++);
                        i1 += 2;
                    }
                    else {
                        flag = true;
                        break;
                    }
                }
            }
            if(flag) {
                break;
            }
        }
        if(!flag && fin[0].size() == 1) {
            cnt_ans = 0;
            print(fin[0][0]);
            printf("Possible\n");
            for(int i = 0; i < cnt_ans; i++) {
                printf("%d", ans[i]);
                if(i + 1 < cnt_ans) {
                    printf(" ");
                }
                else {
                    printf("\n");
                }
            }
        }
        else {
            printf("Impossible\n");
        }
    }
    return 0;
}
