#include <iostream>
#include <numeric>
#include <functional>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>

using namespace std;

class Trie {
    vector<array<int, 26>> tree;

public:
    Trie() : tree(1) {
        tree[0].fill(-1);
    }
    
    template<typename InputIterator>
    void insert(InputIterator begin, InputIterator end) {
        static_assert(is_same<typename iterator_traits<InputIterator>::value_type, char>::value, "");
        for(int cur_node = 0; begin != end; ++begin) {
            char c = *begin;
            if(tree[cur_node][c - 'a'] == -1) {
                tree.emplace_back();
                tree.back().fill(-1);
                tree[cur_node][c - 'a'] = tree.size() - 1;
            }
            cur_node = tree[cur_node][c - 'a'];
        }
    }

    int get_next(int cur, int idx) {
        if(0 <= cur && cur < tree.size() && 0 <= idx && idx < tree[cur].size()) {
            return tree[cur][idx];
        }
        return -1;
    }

    int size() {
        return tree.size();
    }
};

struct InputData {
    int n;
    string str;

    void read_from_stdin() {
        cin >> n >> str;
    }
};

constexpr int MAXM = 10;
constexpr int INF = 1e9;

class Solver {
    InputData input_data;

    Trie trie;
    vector<int> next;

    string ans;

    int build_next(int u) {
        if(u == -1) {
            return 0;
        }

        int res = INF;
        for(int i = 0; i < 26; i++) {
            int cur_res = 1 + build_next(trie.get_next(u, i));
            if(cur_res < res) {
                res = cur_res;
                next[u] = i;
            }
        }

        return res;
    }

    void solve() {
        for(int i = 0; i < input_data.str.length(); i++) {
            int j = min(i + MAXM, (int)input_data.str.length());
            trie.insert(input_data.str.begin() + i, input_data.str.begin() + j);
        }
        next.resize(trie.size());
        build_next(0);

        for(int u = 0; u != -1; u = trie.get_next(u, next[u])) {
            ans.push_back('a' + next[u]);
        }
    }
public:
    Solver(InputData input_data) : input_data(move(input_data)) {
        solve();
    }

    void print_ans() {
        cout << ans << endl;
    }
};

int main() {
    ios::sync_with_stdio(false);
    int t = 1;
    cin >> t;
    while(t--) {
        InputData input_data;
        input_data.read_from_stdin();

        Solver solver(move(input_data));
        solver.print_ans();
    }
    return 0;
}
