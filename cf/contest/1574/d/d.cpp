#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

constexpr int INF = 1e9;

class Solver {
    int n;
    vector<vector<int>> equip_vectors;
    set<vector<int>> banned_builds;

    long long get_score(const vector<int> &build) {
        long long score = 0;
        for(int i = 0; i < n; i++) {
            score += equip_vectors[i][build[i]];
        }
        return score;
    }

    pair<long long, vector<int>> get_first_elem() {
        vector<int> build(n);
        for(int i = 0; i < n; i++) {
            build[i] = equip_vectors[i].size() - 1;
        }
        return {get_score(build), build};
    }

    vector<int> get_ans() {
        set<pair<long long, vector<int>>> que;

        que.emplace(get_first_elem());

        while(!que.empty()) {
            vector<int> top_build = (--que.end())->second;
            que.erase(--que.end());

            if(banned_builds.find(top_build) == banned_builds.end()) {
                return top_build;
            }

            for(int i = 0; i < n; i++) {
                if(top_build[i] > 0) {
                    top_build[i]--;
                    que.emplace(get_score(top_build), top_build);
                    top_build[i]++;
                }
            }

            while(que.size() > banned_builds.size() + 1) {
                que.erase(que.begin());
            }
        }
        return {};
    }

public:
    void read() {
        cin >> n;
        equip_vectors.resize(n);
        for(int i = 0; i < n; i++) {
            int cnt;
            cin >> cnt;
            equip_vectors[i].resize(cnt);
            for(int j = 0; j < cnt; j++) {
                cin >> equip_vectors[i][j];
            }
        }

        int m;
        cin >> m;
        for(int i = 0; i < m; i++) {
            vector<int> banned_build(n);
            for(int j = 0; j < n; j++) {
                cin >> banned_build[j];
                --banned_build[j];
            }
            banned_builds.insert(banned_build);
        }
    }

    void solve() {
        vector<int> ans = get_ans();
        for(int i = 0; i < n; i++) {
            cout << ans[i] + 1 << endl;
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    Solver solver;
    solver.read();
    solver.solve();
    return 0;
}
