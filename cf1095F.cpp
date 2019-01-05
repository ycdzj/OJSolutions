#include <iostream>
#include <vector>
#include <set>
using namespace std;

const int MAXN = 2e5 + 5;
vector<pair<int, long long>> adj[MAXN];
long long a[MAXN];
int n, m;
bool clr[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;
    multiset<pair<long long, int>> rem;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        rem.emplace(a[i], i);
    }

    for(int i = 0; i < m; i++) {
        int x, y; long long w;
        cin >> x >> y >> w;
        adj[x].emplace_back(y, w);
        adj[y].emplace_back(x, w);
    }

    long long cur_min = a[1];
    multiset<pair<long long, int>> cross;
    clr[1] = true;
    for(auto &edg : adj[1]) if(!clr[edg.first]) {
        cross.emplace(edg.second, edg.first);
    }
    rem.erase(rem.find({a[1], 1}));
    long long ans = 0;
    while(!rem.empty()) {
        int nxt;
        while(!cross.empty() && clr[cross.begin()->second]) cross.erase(cross.begin());
        if(!cross.empty() && cur_min + rem.begin()->first > cross.begin()->first) {
            nxt = cross.begin()->second;
            ans += cross.begin()->first;
        }
        else {
            nxt = rem.begin()->second;
            ans += cur_min + rem.begin()->first;
        }
        clr[nxt] = true;
        for(auto &edg : adj[nxt]) if(!clr[edg.first]) {
            cross.emplace(edg.second, edg.first);
        }
        rem.erase(rem.find({a[nxt], nxt}));
        cur_min = min(cur_min, a[nxt]);
    }

    cout << ans << endl;
    return 0;
}
