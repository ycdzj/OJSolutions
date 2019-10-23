#include <cstdio>
#include <vector>
using namespace std;

const int MAXN = 3e5 + 5;

int n;
char str[MAXN];
int main() {
    scanf("%d%s", &n, str);
    vector<int> pos[2];
    long long ans = 0;
    for(int i = n - 1; i >= 0; i--) {
        int val = (str[i] == 'A' ? 0 : 1);
        pos[val].push_back(i);
        if(pos[val].size() >= 2) {
            int p = pos[val][pos[val].size() - 2];
            ans += n - p;
            if(!pos[val ^ 1].empty() && pos[val ^ 1].back() > p) {
                ans--;
            }
        }
    }
    printf("%lld\n", ans);
    return 0;
}
