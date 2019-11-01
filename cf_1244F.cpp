#include <cstdio>
#include <list>
#include <vector>

using namespace std;
const int MAXN = 2e5 + 5;

int n, k;
char str[MAXN];
bool fixed[MAXN];

void flip(int i) {
    if(str[i] == 'B') {
        str[i] = 'W';
    }
    else {
        str[i] = 'B';
    }
}

void solve(list<int> &l) {
    int clk = 0;
    for(int i = 0; !l.empty(); i++) {
        if(i < k) {
            clk ^= 1;
        }
        if(!l.empty()) {
            if(clk) {
                flip(l.front());
            }
            l.pop_front();
        }
        if(!l.empty()) {
            if(clk) {
                flip(l.back());
            }
            l.pop_back();
        }
    }

}
int main() {
    scanf("%d%d", &n, &k);
    scanf("%s", str);
    bool flag = false;
    int s;
    for(int i = 0; i < n; i++) {
        if(str[i] == str[(i + 1) % n] || str[i] == str[(i + n - 1) % n]) {
            fixed[i] = true;
            flag = true;
            s = i;
        }
    }
    if(!flag) {
        if(k & 1) {
            for(int i = 0; i < n; i++) {
                flip(i);
            }
        }
    }
    else {
        list<int> pre;
        for(int i = 1; i <= n; i++) {
            int idx = (s + i) % n;
            if(fixed[idx]) {
                solve(pre);
            }
            else {
                pre.push_back(idx);
            }
        }
    }
    printf("%s\n", str);
    return 0;
}
