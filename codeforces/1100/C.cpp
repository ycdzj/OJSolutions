#include <cstdio>
#include <cmath>
const double PI = acos(-1);
int main() {
    double n, r; scanf("%lf%lf", &n, &r);
    double theta = PI / n;
    double ans = r * sin(theta) / (1 - sin(theta));
    printf("%.7f\n", ans);
    return 0;
}