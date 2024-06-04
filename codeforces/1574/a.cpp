#include <iostream>
using namespace std;

class Solver {
    static void print_bracket(int len) {
        for(int i = 0; i < len; i++) {
            cout << '(';
        }
        for(int i = 0; i < len; i++) {
            cout << ')';
        }
    }

    int n;

public:
    void solve() {
        cin >> n;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < i; j++) {
                print_bracket(1);
            }
            print_bracket(n - i);
            cout << endl;
        }
    }
};

int main() {
    int t;
    cin >> t;
    while(t--) {
        Solver solver;
        solver.solve();
    }
    return 0;
}