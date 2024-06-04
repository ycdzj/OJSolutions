#include <cstdio>
#include <deque>
using namespace std;

const int MAXN = 3e5 + 5;

char str[MAXN];

int main() {
    int q;
    scanf("%d", &q);
    while(q--) {
        scanf("%s", str);
        deque<int> que[2];
        for(int i = 0; str[i] != '\0'; i++) {
            que[(str[i] - '0') % 2].push_back(str[i] - '0');
        }
        while(!que[0].empty() && !que[1].empty()) {
            if(que[0].front() < que[1].front()) {
                printf("%d", que[0].front());
                que[0].pop_front();
            }
            else {
                printf("%d", que[1].front());
                que[1].pop_front();
            }
        }
        while(!que[0].empty()) {
            printf("%d", que[0].front());
            que[0].pop_front();
        }
        while(!que[1].empty()) {
            printf("%d", que[1].front());
            que[1].pop_front();
        }
        printf("\n");
    }
    return 0;
}
