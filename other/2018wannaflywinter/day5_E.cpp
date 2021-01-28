#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

const int MOD = 998244353;
const int MAXN = 3e5 + 5;
const double PI = acos(-1);

struct Complex {
    long double x, y;
};
Complex mul(Complex a, Complex b) {
    return (Complex){a.x * b.x - a.y * b.y, a.x * b.y + b.x * a.y};
}
Complex div(Complex a, long double b) {
    return (Complex){a.x / b, a.y / b};
}
Complex add(Complex a, Complex b) {
    return (Complex){a.x + b.x, a.y + b.y};
}
Complex sub(Complex a, Complex b) {
    return (Complex){a.x - b.x, a.y - b.y};
}
Complex conj(Complex a) {
    return (Complex){a.x, -a.y};
}
Complex inv(Complex a) {
    long double r2 = a.x * a.x + a.y * a.y;
    return (Complex){a.x / r2, -a.y / r2};
}

//fft函数
void fft(Complex a[], int n, bool reverse) {
    static Complex buf[MAXN * 4];
    int lg = 0;
    while((1 << lg) < n) lg++;
    for(int i = 0; i < n; i++) {
        int pos = 0;
        for(int j = 0; j < lg; j++) pos |= ((i >> j & 1) << (lg - 1 - j));
        buf[pos] = a[i];
    }

    for(int i = 0; i < n; i++) a[i] = buf[i];

    for(int l = 1; l < n; l <<= 1) {
        Complex w = (Complex){cos(PI / l), sin(PI / l)};
        if(reverse) w = inv(w);
        for(int i = 0; i < n; i += 2 * l) {
            Complex cur = {1, 0};
            for(int j = 0; j < l; j++) {
                Complex u = a[i + j];
                Complex t = mul(a[i + j + l], cur);
                a[i + j] = add(u, t);
                a[i + j + l] = sub(u, t);
                cur = mul(cur, w);
            }
        }
    }

    if(reverse) {
        for(int i = 0; i < n; i++) {
            a[i] = div(a[i], n);
        }
    }
}
void polymul(Complex res[], Complex a[], Complex b[], int n, int m) {
    int k = 1;
    while(k < n + m - 1) k <<= 1;
    for(int i = n; i < k; i++) a[i] = (Complex){0, 0};
    for(int i = m; i < k; i++) b[i] = (Complex){0, 0};

    fft(a, k, false);
    fft(b, k, false);
    for(int i = 0; i < k; i++) res[i] = mul(a[i], b[i]);
    fft(res, k, true);
}

pair<int, int> a[MAXN], b[MAXN];
int n, m;
long long ans[MAXN * 2];
Complex poly_a[MAXN * 4], poly_b[MAXN * 4], poly_c[MAXN * 4];
int main() {
    freopen("1.txt", "r", stdin);
    scanf("%d%d", &n, &m);
    n++;
    m++;
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i].first);
        a[i].second = i;
    }
    for(int i = 0; i < m; i++) {
        scanf("%d", &b[i].first);
        b[i].second = i;
    }
    sort(a, a + n);
    sort(b, b + n);
    for(int i = 0, j = 0; i < n && j < m; ) {
        if(a[i].first == b[j].first) {
            int cnt_a = 0, cnt_b = 0;
            while(i + cnt_a < n && a[i + cnt_a].first == a[i].first) cnt_a++;
            while(j + cnt_b < m && b[j + cnt_b].first == b[j].first) cnt_b++;
            if((long long)cnt_a * cnt_b < (n + m) * 100) {
                for(int x = i; x < i + cnt_a; x++) for(int y = j; y < j + cnt_b; y++) {
                    ans[a[x].second + b[y].second] += (long long)a[x].second * b[y].second;
                }
            }
            else {
                for(int x = 0; x < n; x++) poly_a[x] = (Complex){0, 0};
                for(int y = 0; y < m; y++) poly_b[y] = (Complex){0, 0};
                for(int x = i; x < i + cnt_a; x++) poly_a[a[x].second].x = a[x].second;
                for(int y = j; y < j + cnt_b; y++) poly_b[b[y].second].x = b[y].second;
                polymul(poly_c, poly_a, poly_b, n, m);
                for(int x = 0; x < n + m - 1; x++) ans[x] += (long long)roundl(poly_c[x].x);
            }
            i += cnt_a;
            j += cnt_b;
        }
        else {
            if(a[i].first < b[j].first) i++;
            else j++;
        }
    }
    for(int i = 0; i < n + m - 1; i++) {
        printf("%lld", ans[i] % MOD);
        if(i + 1 < n + m - 1) printf(" ");
        else printf("\n");
    }
    return 0;
}