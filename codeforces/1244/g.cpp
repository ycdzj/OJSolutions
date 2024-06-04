#include <cstdio>
#include <vector>
using namespace std;

const int MAXN = 1e6 + 6;

int n;
long long k;

int main() {
    scanf("%d%lld", &n, &k);
    long long sum = 0;
    for(int i = 0; i < n; i++) {
        sum += n - i / 2;
    }
    vector<int> ans[2];
    for(int i = n; i >= n + 1 - i; i--) {
        if(i == n + 1 - i) {
            ans[0].push_back(i);
            ans[1].push_back(i);
        }
        else {
            int cur = 2 * i - n - 1;
            long long rem = sum - k;
            if(rem >= cur) {
                ans[0].push_back(i);
                ans[1].push_back(i);
                ans[0].push_back(n + 1 - i);
                ans[1].push_back(n + 1 - i);
                sum -= cur;
            }
            else if(rem > 0 && rem == cur - 1) {
                int j = n + 1 - i;
                ans[0].push_back(i);
                ans[1].push_back(i);
                ans[0].push_back(i - 1);
                ans[1].push_back(j);
                ans[0].push_back(j);
                ans[1].push_back(i - 1);
                if(i - 1 != j + 1) {
                    ans[0].push_back(j + 1);
                    ans[1].push_back(j + 1);
                }
                i--;
                sum -= cur - 1;
            }
            else {
                ans[0].push_back(i);
                ans[1].push_back(n + 1 - i);
                ans[1].push_back(i);
                ans[0].push_back(n + 1 - i);
            }
        }
    }
    if(sum > k) {
        printf("-1\n");
    }
    else {
        printf("%lld\n", sum);
        for(int val : ans[0]) {
            printf("%d ", val);
        }
        printf("\n");
        for(int val : ans[1]) {
            printf("%d ", val);
        }
        printf("\n");
    }
    return 0;
}
