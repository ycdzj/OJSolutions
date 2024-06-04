#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

const int MAXN = 3e5 + 5;

struct Item {
    int d, u, v;
};
bool cmp(Item a, Item b) {
    return a.d > b.d;
}
struct Vertex {
    vector<int> adj;
    int num;
};

Item item[MAXN];
Vertex v[MAXN];
vector<int> dim;
int n;

int main() {
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        scanf("%d", &item[i].d);
        item[i].u = 2 * i + 1;
        item[i].v = 2 * i + 2;
    }
    sort(item, item + n, cmp);
    for(int i = 0; i < item[0].d; i++) {
        v[i].adj.push_back(i + 1);
        dim.push_back(i);
    }
    dim.push_back(item[0].d);
    v[0].num = item[0].u;
    v[item[0].d].num = item[0].v;
    int cur = 1;
    int cnt = item[0].d + 1;

    for(int i = 1; i < item[0].d; i++) {
        v[i].num = item[cur].u;
        int j = i + item[cur].d - 1;
        v[dim[j]].adj.push_back(cnt);
        v[cnt].num = item[cur].v;
        if(j == dim.size() - 1) {
            dim.push_back(cnt);
        }
        cnt++;
        cur++;
    }

    for(; cur < n; cur++) {
        if(item[cur].d == 1) {
            v[0].adj.push_back(cnt);
            v[cnt].num = item[cur].u;
            v[cnt].adj.push_back(cnt + 1);
            v[cnt + 1].num = item[cur].v;
            cnt += 2;
        }
        else {
            v[0].adj.push_back(cnt);
            v[cnt].num = item[cur].u;
            cnt++;

            v[item[cur].d - 2].adj.push_back(cnt);
            v[cnt].num = item[cur].v;
            cnt++;
        }
    }
    for(int i = 0; i < cnt; i++) {
        for(int j : v[i].adj) {
            printf("%d %d\n", v[i].num, v[j].num);
        }
    }
    return 0;
}
