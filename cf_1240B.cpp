#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;

const int MAXN = 3e5 + 5;

struct Item {
    int val, idx;
    bool operator < (const Item &item) const {
        return val < item.val;
    }
};

Item item[MAXN];

int main() {
    int q;
    scanf("%d", &q);
    while(q--) {
        int n;
        scanf("%d", &n);
        for(int i = 0; i < n; i++) {
            int val;
            scanf("%d", &val);
            item[i] = {val, i + 1};
        }
        sort(item, item + n);
        int cnt_val = 0;
        int ans = 0;
        for(int pre_r = 0, pre_cnt = 0, i = 0; i < n; ) {
            cnt_val++;
            int lidx = i;
            int cur_l = n + 1, cur_r = 0;
            while(i < n && item[i].val == item[lidx].val) {
                cur_l = min(cur_l, item[i].idx);
                cur_r = max(cur_r, item[i].idx);
                i++;
            }
            if(pre_r < cur_l) {
                pre_cnt++;
            }
            else {
                pre_cnt = 1;
            }
            pre_r = cur_r;
            ans = max(ans, pre_cnt);
        }
        printf("%d\n", cnt_val - ans);
    }
    return 0;
}
