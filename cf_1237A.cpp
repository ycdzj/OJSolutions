#include <cstdio>

const int MAXN = 1e5 + 5;

int n;
int a[MAXN];
bool flag[MAXN];

int main() {
    scanf("%d", &n);
    long long sum = 0;
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        if(a[i] & 1) {
            flag[i] = true;
        }
        if(a[i] < 0 && (a[i] & 1)) {
            a[i] = a[i] / 2 - 1;
        }
        else {
            a[i] /= 2;
        }
        sum += a[i];
    }
    for(int i = 0; i < n; i++) {
        if(flag[i] && sum < 0) {
            sum++;
            a[i]++;
        }
        printf("%d\n", a[i]);
    }
    return 0;
}
