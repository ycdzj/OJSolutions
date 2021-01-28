#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXM = 1e5;
const int MAXN = 105;
typedef long long ll;

int gcd(int a, int b) {
    if(a == 0) return b;
    return gcd(b % a, a);
}

bool vis[MAXM];
int pri[MAXM], cnt_p;
void init() {
    for(ll i = 2; i < MAXM; i++) {
        if(!vis[i]) {
            for(ll j = i * i; j < MAXM; j += i) {
                vis[j] = true;
            }
        }
    }
    for(int i = 2; i < MAXM; i++) {
        if(!vis[i]) {
            pri[cnt_p++] = i;
        }
    }
}

int buf[MAXN * 2];
ll solve1(int n_) {
    ll ans = 0;
    for(int i = 0; i < n_; i++) {
        int cur = 0;
        for(int j = i; j < n_; j++) {
            cur = gcd(cur, buf[j]);
            if(cur != 1) {
                ans = max(ans, (ll)(j - i + 1));
            }
            else {
                break;
            }
        }
    }
    return ans;
}

struct Item {
    int fac, i, j;
} item[MAXN * MAXN * 400];
int cnt_item;
bool cmp(Item a, Item b) {
    if(a.fac != b.fac) return a.fac < b.fac;
    if(a.i != b.i) return a.i < b.i;
    return a.j < b.j;
}
int board[MAXN * 2][MAXN * 2];
int left[MAXN * 2][MAXN * 2];
int right[MAXN * 2][MAXN * 2];
int height[MAXN * 2][MAXN * 2];
ll solve2() {
    sort(item, item + cnt_item, cmp);
    int ans = 0;
    for(int i = 0; i < cnt_item; ) {
        int nxt_i = i;
        while(nxt_i < cnt_item && item[nxt_i].fac == item[i].fac) nxt_i++;
        for(int j = i; j < nxt_i; j++) {
            int ii = item[j].i, jj = item[j].j, fac = item[j].fac;
            board[ii][jj] = fac;
            left[ii][jj] = 1;
            height[ii][jj] = 1;
            if(jj > 0 && board[ii][jj - 1] == fac) left[ii][jj] += left[ii][jj - 1];
            if(ii > 0 && board[ii - 1][jj] == fac) height[ii][jj] += height[ii - 1][jj];
        }
        for(int j = nxt_i - 1; j >= i; j--) {
            int ii = item[j].i, jj = item[j].j, fac = item[j].fac;
            right[ii][jj] = 1;
            if(board[ii][jj + 1] == fac) right[ii][jj] += right[ii][jj + 1];
        }

        for(int j = i; j < nxt_i; j++) {
            int ii = item[j].i, jj = item[j].j, fac = item[j].fac;
            if(ii > 0 && board[ii - 1][jj] == fac) {
                left[ii][jj] = min(left[ii][jj], left[ii - 1][jj]);
                right[ii][jj] = min(right[ii][jj], right[ii - 1][jj]);
            }
            ans = max(ans, height[ii][jj] * (left[ii][jj] + right[ii][jj] - 1));
        }
        i = nxt_i;
    }
    return ans;
}

int n, m, x, y, mat[MAXN][MAXN];
int main() {
    init();
    scanf("%d%d%d%d", &n, &m, &x, &y);
    int g = 0;
    for(int i = 0; i < n; i++) for(int j = 0; j < m; j++) {
        scanf("%d", &mat[i][j]);
        g = gcd(g, mat[i][j]);
    }
    if(g != 1) {
        printf("%lld\n", (ll)n * m * x * y);
    }
    else {
        ll ans = 0;
        for(int i = 0; i < n; i++) {
            buf[i] = 0;
            for(int j = 0; j < m; j++) buf[i] = gcd(buf[i], mat[i][j]);
        }
        for(int i = n; i < 2 * n; i++) buf[i] = buf[i - n];
        ans = max(ans, solve1(2 * n) * m * y);
        for(int j = 0; j < m; j++) {
            buf[j] = 0;
            for(int i = 0; i < n; i++) buf[j] = gcd(buf[j], mat[i][j]);
        }
        for(int j = m; j < 2 * m; j++) buf[j] = buf[j - m];
        ans = max(ans, solve1(2 * m) * n * x);

        for(int i = 0; i < n; i++) for(int j = 0; j < m; j++) {
            for(int k = 0; k < cnt_p; k++) {
                if(mat[i][j] % pri[k] == 0) {
                    while(mat[i][j] % pri[k] == 0) mat[i][j] /= pri[k];
                    item[cnt_item++] = {pri[k], i, j};
                    if(x >= 2) item[cnt_item++] = {pri[k], i + n, j};
                    if(y >= 2) item[cnt_item++] = {pri[k], i, j + m};
                    if(x >= 2 && y >= 2) item[cnt_item++] = {pri[k], i + n, j + m};
                }
            }
            if(mat[i][j] > 1) {
                item[cnt_item++] = {mat[i][j], i, j};
                if(x >= 2) item[cnt_item++] = {mat[i][j], i + n, j};
                if(y >= 2) item[cnt_item++] = {mat[i][j], i, j + m};
                if(x >= 2 && y >= 2) item[cnt_item++] = {mat[i][j], i + n, j + m};
            }
        }
        ans = max(ans, solve2());
        printf("%lld\n", ans);
    }
    return 0;
}