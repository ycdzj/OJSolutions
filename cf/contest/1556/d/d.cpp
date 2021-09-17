#include <cstdio>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

int query_and(int i, int j) {
    printf("and %d %d\n", i + 1, j + 1);
    fflush(stdout);
    int res;
    scanf("%d", &res);
    return res;
}
int query_or(int i, int j) {
    printf("or %d %d\n", i + 1, j + 1);
    fflush(stdout);
    int res;
    scanf("%d", &res);
    return res;
}

vector<int> encode(vector<int> val) {
    vector<int> res;
    for(int i = 0; i < val.size(); i++) {
        for(int j = i + 1; j < val.size(); j++) {
            res.push_back(val[i] & val[j]);
            res.push_back(val[i] | val[j]);
        }
    }
    return res;
}

map<vector<int>, vector<int>> reverse_map;
int n, k;
vector<int> a;

void get_first_three() {
    int answer_or[3][3], answer_and[3][3];
    for(int i = 0; i < 3; i++) {
        for(int j = i + 1; j < 3; j++) {
            answer_and[i][j] = query_and(i, j);
            answer_or[i][j] = query_or(i, j);
        }
    }
    for(int m = 0; m < 31; m++) {
        vector<int> encoded_val;
        for(int i = 0; i < 3; i++) {
            for(int j = i + 1; j < 3; j++) {
                encoded_val.push_back(answer_and[i][j] >> m & 1);
                encoded_val.push_back(answer_or[i][j] >> m & 1);
            }
        }
        vector<int> origin_val = reverse_map[encoded_val];
        if(origin_val.size() != 3) {
            exit(-1);
        }
        for(int i = 0; i < 3; i++) {
            a[i] ^= (origin_val[i] << m);
        }
    }
}

int main() {
    for(int x = 0; x <= 1; x++) {
        for(int y = 0; y <= 1; y++) {
            for(int z = 0; z <= 1; z++) {
                vector<int> origin = {x, y, z};
                reverse_map[encode(origin)] = origin;
            }
        }
    }
    scanf("%d%d", &n, &k);
    a.resize(n);
    get_first_three();
    for(int i = 3; i < n; i++) {
        int ans_and = query_and(0, i);
        int ans_or = query_or(0, i);
        for(int m = 0; m < 31; m++) {
            if(a[0] >> m & 1) {
                a[i] ^= (ans_and & (1 << m));
            } else {
                a[i] ^= (ans_or & (1 << m));
            }
        }
    }
    nth_element(a.begin(), a.begin() + k - 1, a.end());
    printf("finish %d\n", a[k - 1]);
    return 0;
}