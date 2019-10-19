#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

const int MAXN = 1e5 + 5;
const int INF = 1e9;

int n, m, k;
vector<int> row[MAXN], col[MAXN];

bool solve_1() {
    long long cnt = 1;
    int cur_left = 1, cur_right = m;
    int cur_up = 2, cur_down = n;
    int cur_i = 1, cur_j = 1, dir = 0;
    while(true) {
        long long precnt = cnt;
        if(dir == 0) {
            auto itr = lower_bound(row[cur_i].begin(), row[cur_i].end(), cur_j);
            cnt -= cur_j;
            int val = INF;
            if(itr != row[cur_i].end()) {
                val = *itr - 1;
            }
            cur_j = min(val, cur_right);
            cur_right = cur_j - 1;
            cnt += cur_j;
        }
        else if(dir == 1) {
            auto itr = lower_bound(col[cur_j].begin(), col[cur_j].end(), cur_i);
            cnt -= cur_i;
            int val = INF;
            if(itr != col[cur_j].end()) {
                val = *itr - 1;
            }
            cur_i = min(cur_down, val);
            cur_down = cur_i - 1;
            cnt += cur_i;
        }
        else if(dir == 2) {
            auto itr = lower_bound(row[cur_i].begin(), row[cur_i].end(), cur_j);
            cnt += cur_j;
            int val = -INF;
            if(itr != row[cur_i].begin()) {
                --itr;
                val = *itr + 1;
            }
            cur_j = max(val, cur_left);
            cur_left = cur_j + 1;
            cnt -= cur_j;
        }
        else if(dir == 3) {
            auto itr = lower_bound(col[cur_j].begin(), col[cur_j].end(), cur_i);
            cnt += cur_i;
            int val = -INF;
            if(itr != col[cur_j].begin()) {
                --itr;
                val = *itr + 1;
            }
            cur_i = max(val, cur_up);
            cur_up = cur_i + 1;
            cnt -= cur_i;
        }
        if(precnt == cnt) {
            break;
        }
        dir = (dir + 1) % 4;
    }
    return cnt + k == (long long)n * m;
}
bool solve_2() {
    long long cnt;
    if(col[1].empty()) {
        cnt = n;
    }
    else {
        cnt = col[1][0] - 1;
    }
    return cnt + k == (long long)n * m;
}
int main() {
    scanf("%d%d%d", &n, &m, &k);
    for(int i = 0; i < k; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        row[x].push_back(y);
        col[y].push_back(x);
    }
    for(int i = 1; i <= n; i++) {
        sort(row[i].begin(), row[i].end());
    }
    for(int i = 1; i <= m; i++) {
        sort(col[i].begin(), col[i].end());
    }

    if(solve_1() || solve_2()) {
        printf("Yes\n");
    }
    else {
        printf("No\n");
    }
    return 0;
}
