#include <cstdio>
#include <vector>
using namespace std;

const int MAXM = 21;
const int MASK = 1 << MAXM;
const int MAXN = 1e6 + 6;

vector<int> f[MASK];

void update(int i, int val) {
    for(auto x : f[i]) {
        if(x == val) {
            return;
        }
    }
    if(f[i].size() < 2) {
        f[i].push_back(val);
        if(f[i].size() == 2 && f[i][0] < f[i][1]) {
            swap(f[i][0], f[i][1]);
        }
    }
    else {
        if(val >= f[i][0]) {
            f[i][1] = f[i][0];
            f[i][0] = val;
        }
        else if(val >= f[i][1]) {
            f[i][1] = val;
        }
    }
}

int n, a[MAXN];

bool check(int val, int i) {
    return f[val].size() >= 2 && f[val][1] > i;
}
int main() {
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        update(a[i], i);
    }
    for(int i = MASK - 1; i >= 0; i--) {
        for(int j = 0; j < MAXM; j++) {
            if(i >> j & 1) {
                for(int k = 0; k < f[i].size(); k++) {
                    update((i ^ (1 << j)), f[i][k]);
                }
            }
        }
    }
    int ans = 0;
    for(int i = 0; i < n - 2; i++) {
        int mask = 0;
        for(int j = MAXM - 1; j >= 0; j--) {
            if(!(a[i] >> j & 1)) {
                mask ^= (1 << j);
                if(!check(mask, i)) {
                    mask ^= (1 << j);
                }
            }
        }
        ans = max(ans, (a[i] | mask));
    }
    printf("%d\n", ans);
    return 0;
}
