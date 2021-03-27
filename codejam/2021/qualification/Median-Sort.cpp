#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

int query(int a, int b, int c) {
    printf("%d %d %d\n", a, b, c);
    fflush(stdout);
    int ans;
    scanf("%d", &ans);
    if(ans == -1) {
        exit(0);
    }
    return ans;
}

void answer(const vector<int> &a) {
    for(int i = 0; i < a.size(); i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
    fflush(stdout);
    int ans;
    scanf("%d", &ans);
    if(ans == -1) {
        exit(0);
    }
}

int main() {
    int t, n, q;
    scanf("%d%d%d", &t, &n, &q);
    for(int i_case = 1; i_case <= t; i_case++) {
        vector<int> a{1, 2};
        for(int i = 3; i <= n; i++) {
            int l = 0, r = a.size() - 1;
            while(true) {
                int len = r - l + 1;
                if(len == 2) {
                    int res = query(a[l], a[r], i);
                    if(res == a[l]) {
                        a.insert(a.begin() + l, i);
                        break;
                    }
                    if(res == i) {
                        a.insert(a.begin() + r, i);
                        break;
                    }
                    a.insert(a.begin() + r + 1, i);
                    break;
                }
                if(rand() % 2 == 0) {
                    int mid = (l + r + 1) / 2;
                    int res = query(a[l], a[mid], i);
                    if(res == a[l]) {
                        a.insert(a.begin() + l, i);
                        break;
                    }
                    if(res == i) {
                        if(mid - l - 1 == 0) {
                            a.insert(a.begin() + mid, i);
                            break;
                        }
                        l = l + 1;
                        r = mid - 1;
                        if(l == r) {
                            if(rand() % 2 == 0) {
                                l--;
                            } else {
                                r++;
                            }
                        }
                        continue;
                    }
                    if(res == a[mid]) {
                        l = mid + 1;
                        if(l == r) {
                            l--;
                        }
                        continue;
                    }
                } else {
                    int mid = (l + r) / 2;
                    int res = query(a[mid], a[r], i);
                    if(res == a[r]) {
                        a.insert(a.begin() + r + 1, i);
                        break;
                    }
                    if(res == i) {
                        if(r - mid - 1 == 0) {
                            a.insert(a.begin() + r, i);
                            break;
                        }
                        l = mid + 1;
                        r = r - 1;
                        if(l == r) {
                            if(rand() % 2 == 0) {
                                l--;
                            } else {
                                r++;
                            }
                        }
                        continue;
                    }
                    if(res == a[mid]) {
                        r = mid - 1;
                        if(l == r) {
                            r++;
                        }
                        continue;
                    }
                }
            }
        }
        answer(a);
    }
    return 0;
}