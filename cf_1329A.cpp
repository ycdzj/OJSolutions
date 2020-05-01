#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    bool ans = true;
    long long sum = 0;
    vector<int> v;
    for(int i = 0; i < m; i++) {
        int l;
        cin >> l;
        v.push_back(l);
        if(i + l > n) {
            ans = false;
        }
        sum += l;
    }
    if(sum < (long long)n) {
        ans = false;
    }
    if(ans) {
        vector<int> pos(m);
        pos[m - 1] = m - 1 + v[m - 1];
        for(int i = m - 2; i >= 0; i--) {
            pos[i] = i + v[i];
            pos[i] = max(pos[i], pos[i + 1]);
        }
        int pre = 0;
        for(int i = 1; i < m; i++) {
            cout << pre + 1 << endl;
            pre = min(pre + v[i - 1], n + i - pos[i]);
        }
        cout << pre + 1 << endl;
    } else {
        cout << -1 << endl;
    }
    return 0;
}
