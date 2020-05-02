#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
    int t;
    scanf("%d", &t);
    while(t-- > 0) {
        int n;
        scanf("%d", &n);
        int rem = n - 1, day = 0, x = 1;
        vector<int> ans;
        while(rem > 0) {
            int y;
            if(rem <= 2 * x) {
                y = rem;
            } else {
                y = min(2 * x, rem / 2);
            }
            ans.push_back(y - x);

            x = y;
            rem -= x;
            day++;
        }
        printf("%d\n", day);
        for(int i = 0; i < ans.size(); i++) {
            printf("%d ", ans[i]);
        }
        printf("\n");
    }

    return 0;
}
