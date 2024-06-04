#include <cstdio>
#include <bitset>
using namespace std;

const int MAXN = 1e5 + 5;
const int MAXM = 7005;

bool pri[MAXM];
int mob[MAXM];
bitset<MAXM> divset[MAXM], curset[MAXN], invset[MAXM];

int main() {
    for(int i = 1; i < MAXM; i++) mob[i] = 1;
    for(int i = 2; i < MAXM; i++) if(!pri[i]) {
        mob[i] = -1;
        for(int j = 2 * i; j < MAXM; j += i) {
            pri[j] = true;
            if(j % (i * i) == 0) mob[j] = 0;
            else mob[j] = -mob[j];
        }
    }
    for(int i = 1; i < MAXM; i++) {
        for(int j = 1; j * j <= i; j++) if(i % j == 0) {
            divset[i].set(j);
            divset[i].set(i / j);
        }
        for(int j = 1; j * i < MAXM; j++) {
            if(mob[j] != 0) invset[i].set(j * i);
        }
    }
    int n, q;
    scanf("%d%d", &n, &q);
    while(q--) {
        int cmd; scanf("%d", &cmd);
        if(cmd == 1) {
            int x, v; scanf("%d%d", &x, &v);
            curset[x] = divset[v];
        }
        else if(cmd == 2) {
            int x, y, z; scanf("%d%d%d", &x, &y, &z);
            curset[x] = curset[y] ^ curset[z];
        }
        else if(cmd == 3) {
            int x, y, z; scanf("%d%d%d", &x, &y, &z);
            curset[x] = curset[y] & curset[z];
        }
        else if(cmd == 4) {
            int x, v; scanf("%d%d", &x, &v);
            putchar('0' + (curset[x] & invset[v]).count() % 2);
        }
    }
    return 0;
}