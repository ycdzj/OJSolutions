#include <cstdio>
#include <queue>
#include <deque>
#include <algorithm>
using namespace std;

const int MAXN = 1e5 + 5;

struct Person {
    long long t;
    int idx;
};

bool cmp(Person a, Person b) {
    if(a.t == b.t) {
        return a.idx < b.idx;
    }
    return a.t < b.t;
}

int n;
long long p;
Person person[MAXN], person_arr[MAXN];
long long ans[MAXN];

long long last;
void pop_person(deque<pair<Person, long long>> &queing) {
    last = queing.front().second + p;
    ans[queing.front().first.idx] = last;
    queing.pop_front();
    if(!queing.empty()) {
        queing.front().second = last;
    }
}

int main() {
    scanf("%d%lld", &n, &p);
    for(int i = 0; i < n; i++) {
        scanf("%lld", &person[i].t);
        person[i].idx = i;
        person_arr[i] = person[i];
    }
    sort(person, person + n, cmp);

    deque<pair<Person, long long>> queing;
    priority_queue<int, vector<int>, greater<int>> waiting;

    for(int i = 0; i < n; i++) {
        if(!queing.empty()) {
            while(!queing.empty() && queing.front().second + p <= person[i].t) {
                pop_person(queing);
            }
            while(queing.empty() && last < person[i].t && !waiting.empty()) {
                int idx = waiting.top();
                queing.push_back({person_arr[idx], last});
                waiting.pop();
                if(queing.front().second + p <= person[i].t) {
                    pop_person(queing);
                }
                else {
                    break;
                }
            }
        }

        if(queing.empty()) {
            waiting.push(person[i].idx);
            last = person[i].t;
            int idx = waiting.top();
            queing.push_back({person_arr[idx], last});
            waiting.pop();
        }
        else {
            if(queing.back().first.idx > person[i].idx) {
                queing.push_back({person[i], 0});
            }
            else {
                waiting.push(person[i].idx);
            }
        }
    }
    while(!queing.empty()) {
        pop_person(queing);
    }
    while(!waiting.empty()) {
        int idx = waiting.top();
        queing.push_back({person_arr[idx], last});
        waiting.pop();
        pop_person(queing);
    }
    for(int i = 0; i < n; i++) {
        printf("%lld ", ans[i]);
    }
    printf("\n");
    return 0;
}
