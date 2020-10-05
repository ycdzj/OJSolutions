#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 1e5 + 5;

char str[MAXN];

class Value {
public:
    char c1, c2, last_c1, last_c2;
    int pos, l1, sz;

    Value() {
        c1 = 0;
        c2 = 0;
        pos = 0;
        l1 = 0;
        last_c1 = 0;
        last_c2 = 0;
    }

    void push_front(char c) {
        if(c == c1) {
            l1++;
        } else {
            c2 = c1;
            c1 = c;
            l1 = 1;
        }
        if(last_c2 == 0) {
            last_c2 = c;
        } else if(last_c1 == 0) {
            last_c1 = c;
        }
        sz++;
    }

    bool operator < (const Value &value) const {
        if(c1 != value.c1) {
            return c1 < value.c1;
        }
        char cl = c1, cr = c1;
        if(l1 < value.l1) {
            cl = c2;
        } else if(value.l1 < l1) {
            cr = value.c2;
        }
        return cl < cr;
    }
} f[MAXN];

void print(int idx, int cnt) {
    for(int i = 0; i < cnt; i++) {
        putchar(f[idx].c1);
        idx = f[idx].pos + 1;
    }
}

int main() {
    scanf("%s", str);
    int len = strlen(str);

    f[len].pos = len;
    for(int i = len - 1; i >= 0; i--) {
        f[i] = f[i + 1];
        f[i].push_front(str[i]);
        f[i].pos = i;
        if(i + 1 < len && str[i] == str[i + 1]) {
            f[i] = min(f[i], f[i + 2]);
        }
    }

    for(int i = 0; i < len; i++) {
        printf("%d ", f[i].sz);
        if(f[i].sz <= 10) {
            print(i, f[i].sz);
            putchar('\n');
        } else {
            print(i, 5);
            printf("...%c%c\n", f[i].last_c1, f[i].last_c2);
        }
    }
    return 0;
}
