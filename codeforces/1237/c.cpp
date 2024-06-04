#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN = 1e5 + 5;

struct Point {
    int x, y, z, idx;
    bool operator < (const Point &p) const {
        if(x != p.x) {
            return x < p.x;
        }
        if(y != p.y) {
            return y < p.y;
        }
        return z < p.z;
    }
};

int n;
Point points[MAXN];

int solve_1(int l, int r) {
    int pre_item = -1;
    for(int i = l; i <= r; i++) {
        if(pre_item == -1) {
            pre_item = i;
        }
        else {
            printf("%d %d\n", points[pre_item].idx, points[i].idx);
            pre_item = -1;
        }
    }
    return pre_item;
}

int solve_2(int l, int r) {
    int pre_item = -1;
    for(int i = l, pre_i = l; i <= r; i++) {
        if(i == r || points[i].y != points[i + 1].y) {
            int cur_item = solve_1(pre_i, i);
            if(cur_item != -1) {
                if(pre_item != -1) {
                    printf("%d %d\n", points[cur_item].idx, points[pre_item].idx);
                    pre_item = -1;
                }
                else {
                    pre_item = cur_item;
                }
            }
            pre_i = i + 1;
        }
    }
    return pre_item;
}

int main() {
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        scanf("%d%d%d", &points[i].x, &points[i].y, &points[i].z);
        points[i].idx = i + 1;
    }
    sort(points, points + n);
    for(int i = 0, pre_i = 0, pre_item = -1; i < n; i++) {
        if(i == n - 1 || points[i].x != points[i + 1].x) {
            int cur_item = solve_2(pre_i, i);
            if(cur_item != -1) {
                if(pre_item != -1) {
                    printf("%d %d\n", points[cur_item].idx, points[pre_item].idx);
                    pre_item = -1;
                }
                else {
                    pre_item = cur_item;
                }
            }
            pre_i = i + 1;
        }
    }
    return 0;
}
