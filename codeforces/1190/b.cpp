#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN = 1e5 + 5;

int n, a[MAXN];

int main() {
    scanf("%d", &n);
    bool flag = false;
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        if(a[i]) {
            flag = true;
        }
    }
    sort(a, a + n);
    int cnt = 0;
    for(int i = 1; i < n; i++) {
        if(a[i] == a[i - 1]) {
            cnt++;
            if(a[i] == 0) {
                flag = false;
                break;
            }
            if(i >= 2 && a[i - 1] - 1 == a[i - 2]) {
                flag = false;
                break;
            }
        }
    }
    if(!flag || cnt > 1) {
        printf("cslnb\n");
    }
    else {
        bool rev = false;
        if(cnt == 1) {
            for(int i = 1; i < n; i++) {
                if(a[i] == a[i - 1]) {
                    a[i - 1]--;
                    break;
                }
            }
            rev = true;
        }
        long long sum = 0;
        for(int i = 0; i < n; i++) {
            sum += a[i] - i;
        }
        sum = sum % 2;
        if(rev) {
            sum = 1 - sum;
        }
        if(sum) {
            printf("sjfnb\n");
        }
        else {
            printf("cslnb\n");
        }
    }
    return 0;
}
