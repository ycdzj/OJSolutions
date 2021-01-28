#include <cstdio>

int gcd(int a, int b) {
    if(b == 0) {
        return a;
    }
    return gcd(b, a % b);
}
int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        int n;
        scanf("%d", &n);
        int pow_f, pow_g, aug_f, aug_g;
        for(int i = 0; i < n; i++) {
            int a; scanf("%d", &a);
            if(a > 0) {
                pow_f = i;
                aug_f = a;
            }
        }
        for(int i = 0; i< n; i++) {
            int a; scanf("%d", &a);
            if(a > 0) {
                pow_g = i;
                aug_g = a;
            }
        }
        if(pow_f == pow_g) {
            int g = gcd(aug_f, aug_g);
            printf("%d/%d\n", aug_f / g, aug_g / g);
        }
        else if(pow_f < pow_g) {
            printf("0/1\n");
        }
        else {
            printf("1/0\n");
        }
    }
    return 0;
}