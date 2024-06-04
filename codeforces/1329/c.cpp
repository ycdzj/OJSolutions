#include <iostream>
#include <vector>
#include <memory>
using namespace std;

class Solver {
public:
    void input() {
        cin >> h >> g;
        int n = (1 << h);
        a.resize(n);
        seq.clear();
        for(int i = 1; i < n; i++) {
            cin >> a[i];
        }
    }
    void print() {
        cout << solve() << endl;
        for(int i = 0; i < seq.size(); i++) {
            cout << seq[i] << ' ';
        }
        cout << endl;
    }
private:
    int h, g;
    vector<int> a;
    vector<int> seq;
    int get_val(int i) {
        if(i < a.size()) {
            return a[i];
        }
        return 0;
    }
    void f(int i) {
        int left = (i << 1);
        int right = (i << 1 | 1);
        int left_val = get_val(left);
        int right_val = get_val(right);
        if(left_val == 0 && right_val == 0) {
            a[i] = 0;
            return;
        }
        if(left_val > right_val) {
            a[i] = left_val;
            f(left);
        } else {
            a[i] = right_val;
            f(right);
        }
    }
    int get_height(int i) {
        if(i >= a.size() || a[i] == 0) {
            return 0;
        }
        int left = (i << 1);
        int right = (i << 1 | 1);
        int left_val = get_val(left);
        int right_val = get_val(right);
        if(left_val > right_val) {
            return 1 + get_height(left);
        }
        return 1 + get_height(right);
    }
    void calc(int i, int target) {
        if(get_val(i) == 0) {
            return;
        }
        while(get_height(i) > target) {
            f(i);
            seq.push_back(i);
        }
        calc(i << 1, target - 1);
        calc(i << 1 | 1, target - 1);
    }
    long long solve() {
        calc(1, g);
        long long ans = 0;
        for(int i = 1; i < (1 << g); i++) {
            ans += a[i];
        }
        return ans;
    }
};

int main() {
    ios::sync_with_stdio(false);
    int t;
    cin >> t;
    while(t-- > 0) {
        shared_ptr<Solver> solver(new Solver());
        solver->input();
        solver->print();
    }
    return 0;
}