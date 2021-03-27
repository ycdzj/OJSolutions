#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 105;
const int MAXM = 10005;

int n, m;
char a[MAXN][MAXM];

double get_x(double y) {
    return log(y) - log(1 - y);
}

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
        for(int i = 0; i < n; i++) {
            int cnt_one = 0;
            vector<double> x_list;
            for(int j = 0; j < m; j++) {
                if(a[i][idx_list[j]] == '1') {
                    cnt_one++;
                }
                if(j % 1000 == 999) {
                    x_list.push_back(get_x((double)cnt_one / 1000));
                    cnt_one = 0;
                }
            }
            printf("%d: ", i + 1);
            for(int i = 1; i < x_list.size(); i++) {
                printf("%.04f ", x_list[i] - x_list[i - 1]);
            }
            printf("\n");
        }
        printf("Case #%d: %d\n", i_case, ans_idx + 1);
    }
    return 0;
}