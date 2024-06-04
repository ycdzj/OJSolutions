#include <cstdio>
#include <algorithm>
#include <deque>
#include <vector>
using namespace std;


int main() {
    int n, q;
    scanf("%d%d", &n, &q);
    deque<int> que;
    int max_val = 0;
    for(int i = 0; i < n; i++) {
        int a;
        scanf("%d", &a);
        que.push_back(a);
        max_val = max(max_val, a);
    }
    vector<pair<int, int>> ans;
    while(que.front() != max_val) {
        int a = que.front();
        que.pop_front();
        int b = que.front();
        que.pop_front();
        ans.push_back({a, b});
        if(a < b) {
            swap(a, b);
        }
        que.push_front(a);
        que.push_back(b);
    }
    vector<int> arr;
    while(!que.empty()) {
        arr.push_back(que.front());
        que.pop_front();
    }
    while(q--) {
        long long x;
        scanf("%lld", &x);
        --x;
        pair<int, int> cur_ans;
        if(x < ans.size()) {
            cur_ans = ans[x];
        }
        else {
            x -= ans.size();
            cur_ans = make_pair(max_val, arr[x % (n - 1) + 1]);
        }
        printf("%d %d\n", cur_ans.first, cur_ans.second);
    }
    return 0;
}
