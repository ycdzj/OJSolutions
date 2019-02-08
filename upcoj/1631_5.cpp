#include <cstdio>
#include <algorithm>
int c[3], m[3];
int main() {
    for(int i = 0; i < 3; i++) scanf("%d%d", &c[i], &m[i]);
    for(int i = 0; i < 100; i++) {
        int cur = i % 3;
        int nxt = (i + 1) % 3;
        int p = std::min(m[cur], c[nxt] - m[nxt]);
        m[cur] -= p;
        m[nxt] += p;
    }
    for(int i = 0; i < 3; i++) printf("%d\n", m[i]);
    return 0;
}