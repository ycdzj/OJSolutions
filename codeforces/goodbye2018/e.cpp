#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
const int MAXN = 5e5 + 5;

int n;
vector<int> a;
long long sum;

int check(int x) {
    a.insert(lower_bound(a.begin(), a.end(), x), x);
    sum += x;

    long long cursum = 0, prefixsum = 0;
    int res = 0;
    for(int k = 1, p = 0; k <= a.size(); k++) {
        while(p < a.size() && a[p] <= k) {
            prefixsum += a[p++];
        }
        cursum += a[a.size() - k];
        if(p <= a.size() - k) {
            if(prefixsum + (long long)k * (a.size() - k - p) + (long long)k * (k - 1) < cursum) {
                res = (a[a.size() - k] <= x) ? 1 : -1;
                break;
            }
        }
        else {
            if(sum - cursum + (long long)k * (k - 1) < cursum) {
                res = (a[a.size() - k] <= x) ? 1 : -1;
                break;
            }
        }
    }

    sum -= x;
    a.erase(lower_bound(a.begin(), a.end(), x));
    return res;
}

int main() {
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        int val; scanf("%d", &val);
        a.push_back(val);
        sum += val;
    }
    sort(a.begin(), a.end());
    int mask = (int)(sum & 1);
    int l1 = 0, r1 = n;
    while(l1 < r1) {
        int mid = (l1 + r1) / 2;
        if(check(mid << 1 | mask) == -1) l1 = mid + 1;
        else r1 = mid;
    }
    int l2 = 0, r2 = n;
    while(l2 < r2) {
        int mid = (l2 + r2 + 1) / 2;
        if(check(mid << 1 | mask) == 1) r2 = mid - 1;
        else l2 = mid;
    }
    if(check(l1 << 1 | mask) != 0) l1++;
    if(check(l2 << 1 | mask) != 0) l2--;
    if(l1 > l2) printf("-1\n");
    else {
        for(int i = l1; i <= l2; i++) printf("%d ", (i << 1 | mask));
        printf("\n");
    }
    return 0;
}
