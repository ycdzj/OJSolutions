#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 105;
const int MAXM = 10005;

int n, m;
char a[MAXN][MAXM];

int main() {
    int t, p;
    scanf("%d%d", &t, &p);
    for(int i_case = 1; i_case <= t; i_case++) {
        n = 100;
        m = 10000;
        for(int i = 0; i < n; i++) {
            scanf("%s", a[i]);
        }
        vector<int> cnt_correct(m);
        vector<int> idx_list(m);
        for(int j = 0; j < m; j++) {
            for(int i = 0; i < n; i++) {
                if(a[i][j] == '1') {
                    cnt_correct[j]++;
                }
            }
            idx_list[j] = j;
        }
        sort(idx_list.begin(), idx_list.end(), [&](int x, int y)->bool{
            return cnt_correct[x] < cnt_correct[y];
        });
        int ans_idx = 0;
        double ans_score = -1;
        for(int i = 0; i < n; i++) {
            int cnt_one = 0;
            int cnt_inv = 0;
            for(int j = 0; j < m; j++) {
                if(a[i][idx_list[j]] == '0') {
                    cnt_inv += cnt_one;
                } else {
                    cnt_one++;
                }
            }
            double score = cnt_inv;
            score /= cnt_one;
            score /= m - cnt_one;
            if(score > ans_score) {
                ans_score = score;
                ans_idx = i;
            }
        }
        printf("Case #%d: %d\n", i_case, ans_idx + 1);
    }
    return 0;
}