#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

double get_pos(double cur_time, vector<int> &a) {
    double cur_pos = 0;
    for(int i = 0; i < a.size(); i++) {
        double cur_spd = i + 1;
        double t = (a[i] - cur_pos) / cur_spd;
        if(t <= cur_time) {
            cur_time -= t;
            cur_pos = a[i];
        } else {
            cur_pos += cur_time * cur_spd;
            cur_time = 0;
            break;
        }
    }
    cur_pos += (a.size() + 1) * cur_time;
    return cur_pos;
}

int main() {
    int t;
    scanf("%d", &t);
    while(t--) {
        int n, l;
        scanf("%d%d", &n, &l);
        vector<int> a(n);
        vector<int> rev_a(n);
        for(int i = 0; i < n; i++) {
            scanf("%d", &a[i]);
            rev_a[n - 1 - i] = l - a[i];
        }
        double left = 0, right = 2e9;
        for(int i = 0; i < 100; i++) {
            double mid = (right + left) / 2;
            if(get_pos(mid, a) + get_pos(mid, rev_a) >= l) {
                right = mid;
            } else {
                left = mid;
            }
        }
        printf("%.10f\n", (left + right) / 2);
    }
    return 0;
}