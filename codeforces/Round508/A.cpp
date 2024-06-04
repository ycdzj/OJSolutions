#include <cstdio>
#include <algorithm>
int n, k;
char str[100005];
int cnt[26];
int main() {
    scanf("%d%d", &n, &k);
    scanf("%s", str);
    for(int i = 0; i < n; i++) cnt[str[i] - 'A']++;
    int ans = n;
    for(int i = 0; i < k; i++) ans = std::min(ans, cnt[i]);
    printf("%d\n", ans * k);
    return 0;
}