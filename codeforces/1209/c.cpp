#include <cstdio>
#include <vector>
using namespace std;
const int MAXN = 2e5 + 5;

int n;
char str[MAXN];
bool clr[MAXN];

int main() {
    int t;
    scanf("%d", &t);
    while(t--) {
        scanf("%d%s", &n, str);
        bool ans = false;
        for(int k = 0; k <= 9; k++) {
            int cur[2] = {0, 0};
            int firstIdx = -1, lastIdx = -1;
            bool flag = true;
            for(int i = 0; i < n; i++) {
                int val = str[i] - '0';
                if(val < k) {
                    lastIdx = i;
                    if(cur[0] <= val) {
                        cur[0] = val;
                    }
                    else {
                        flag = false;
                    }
                }
                else if(val > k) {
                    if(firstIdx == -1) {
                        firstIdx = i;
                    }
                    if(cur[1] <= val) {
                        cur[1] = val;
                    }
                    else {
                        flag = false;
                    }
                }
            }
            if(flag) {
                for(int i = 0; i < n; i++) {
                    int val = str[i] - '0';
                    if(val == k) {
                        if(lastIdx == -1 || i >= lastIdx) {
                            clr[i] = true;
                        }
                        else if(firstIdx == -1 || i <= firstIdx) {
                            clr[i] = false;
                        }
                        else {
                            flag = false;
                        }
                    }
                }
            }
            if(flag) {
                ans = true;
                for(int i = 0; i < n; i++) {
                    int val = str[i] - '0';
                    if(val < k) {
                        putchar('1');
                    }
                    else if(val > k) {
                        putchar('2');
                    }
                    else {
                        if(clr[i]) {
                            putchar('1');
                        }
                        else {
                            putchar('2');
                        }
                    }
                }
                putchar('\n');
                break;
            }
        }
        if(!ans) {
            printf("-\n");
        }
    }
    return 0;
}
