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

struct InputData {
    int n;
    string str;

    void read_from_stdin() {
        cin >> n >> str;
    }
};

int gcd(int a, int b) {
    if(a == 0) {
        return b;
    }
    return gcd(b % a, a);
}

class Solver {
    vector<int> ans;
public:
    Solver(InputData in) {
        map<pair<int, int>, int> cnt;
        for(int i = 0, cnt_d = 0, cnt_k = 0; i < in.n; i++) {
            if(in.str[i] == 'D') {
                cnt_d++;
            } else {
                cnt_k++;
            }

            int g = gcd(cnt_d, cnt_k);
            ans.push_back(++cnt[{cnt_d / g, cnt_k / g}]);
        }
    }

    void print_ans() {
        for(int val : ans) {
            cout << val << ' ';
        }
        cout << endl;
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
