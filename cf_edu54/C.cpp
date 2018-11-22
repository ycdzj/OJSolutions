#include <cstdio>
#include <cmath>

int main() {
    int T; scanf("%d", &T);
    while(T--) {
        double d; scanf("%lf", &d);
        if(d == 0) {
            printf("Y 0 0\n");
            continue;
        }
        if(d < 4) {
            printf("N\n");
            continue;
        }
        double delta = sqrt(d * (d - 4));
        double b1 = (d + delta) / 2;
        double b2 = (d - delta) / 2;
        double a1 = d - b1;
        double a2 = d - b2;
        if(fabs(a1 + b1 - a1 * b1) <= 1e-6 && fabs(a1 + b1 - d) <= 1e-6) printf("Y %.9f %.9f\n", a1, b1);
        else printf("Y %.9f %.9f\n", a2, b2);
    }
    return 0;
}