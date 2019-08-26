#include <cstdio>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

const int MAXN = 1e6 + 6;

int n, w;
vector<int> arr[MAXN];
multiset<int> cur[MAXN];
vector<int> addZero[MAXN], rmZero[MAXN];
int idx[MAXN];

bool cmp(int a, int b) {
    return arr[a].size() < arr[b].size();
}
int main() {
    scanf("%d%d", &n, &w);
    for(int i = 0; i < n; i++) {
        int l;
        scanf("%d", &l);
        arr[i].resize(l);
        for(int j = 0; j < l; j++) {
            scanf("%d", &arr[i][j]);
        }
        idx[i] = i;
        cur[i].insert(-1e9);
        cur[i].insert(0);
        addZero[l].push_back(i);
        rmZero[w - l].push_back(i);
    }
    sort(idx, idx + n, cmp);
    long long ans = 0;
    for(int j = 0; j < w; j++) {
        for(auto i : addZero[j]) {
            ans -= *cur[i].rbegin();
            cur[i].insert(0);
            ans += *cur[i].rbegin();
        }
        for(auto i : rmZero[j]) {
            ans -= *cur[i].rbegin();
            cur[i].erase(cur[i].find(0));
            ans += *cur[i].rbegin();
        }
        for(int k = n - 1; k >= 0; k--) {
            int i = idx[k];
            if(j < arr[i].size()) {
                ans -= *cur[i].rbegin();
                cur[i].insert(arr[i][j]);
                ans += *cur[i].rbegin();
            }
            else {
                break;
            }
        }
        printf("%lld ", ans);
        for(int k = n - 1; k >= 0; k--) {
            int i = idx[k];
            if(j - w + (int)arr[i].size() >= 0) {
                ans -= *cur[i].rbegin();
                cur[i].erase(cur[i].find(arr[i][j - w + (int)arr[i].size()]));
                ans += *cur[i].rbegin();
            }
            else {
                break;
            }
        }
    }
    printf("\n");
    return 0;
}
