#include <cstdio>
#include <stack>
using namespace std;

int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        long long a, b, c, d;
        scanf("%lld%lld%lld%lld", &a, &b, &c, &d);
        if(a == b || c == d) {
            if(a == b && b == c && c == d) {
                printf("Yes\n");
                printf("\n");
            }
            else {
                printf("No\n");
            }
        }
        else {
            if((a < b) != (c < d)) {
                printf("No\n");
            }
            else {
                bool toggle = false;
                if(a > b) {
                    swap(a, b);
                    swap(c, d);
                    toggle = true;
                }
                long long d1 = d - c, d2 = b - a;
                while(d2 < d1) {
                    d2 *= 2;
                }
                if(d1 != d2) {
                    printf("No\n");
                    continue;
                }
                if(c <= a && b <= d) {
                    bool flag = true;
                    stack<int> ans;
                    while(c <= a && b <= d) {
                        if(c == a && b == d) {
                            break;
                        }
                        long long m = (c + d) / 2;
                        if((c + d) % 2 == 1) {
                            flag = false;
                            break;
                        }
                        if(b <= m) {
                            d = m;
                            ans.push(0);
                        }
                        else if(m <= a) {
                            c = m;
                            ans.push(1);
                        }
                        else {
                            flag = false;
                            break;
                        }
                    }
                    if(!flag) {
                        printf("No\n");
                    }
                    else {
                        printf("Yes\n");
                        char str[2] = {'A', 'B'};
                        if(toggle) {
                            swap(str[0], str[1]);
                        }
                        while(!ans.empty()) {
                            putchar(str[ans.top()]);
                            ans.pop();
                        }
                        putchar('\n');
                    }
                }
                else {
                    printf("No\n");
                }
            }
        }
    }
    return 0;
}
