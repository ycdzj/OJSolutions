#include <iostream>
using namespace std;

const long long HIGH = 60;

int get_cnt(long long x) {
    int res = 0;
    while(x) {
        if(x & 1) {
            res++;
        }
        x >>= 1;
    }
    return res;
}

long long prefix(long long x, long long n) {
    int cnt = get_cnt(x);
    long long res = 0;
    for(int i = HIGH; i >= 0; i--) {
        if(x >> i & 1) {
            cnt--;
        }
        if(n >> i & 1) {
            res += ((long long)1 << (i - cnt));
            if(x >> i & 1) {
                break;
            }
        }
    }
    return res;
}

long long g(long long l, long long r) {
    if(l == 0) {
        return 2 * r - 1;
    }
    return 2 * (prefix(l, r) - prefix(l, l));
}

long long h(long long l, long long r) {
    if(r == 0) {
        return 0;
    }
    if(r == 1) {
        return 1;
    }
    return 2 * (prefix(r - 1, r) - prefix(r - 1, l));
}

long long f(long long l, long long r) {
    if(l == r) {
        return 0;
    }
    if(l & 1) {
        return f(l - 1, r) - g(l - 1, r);
    }
    else if(r & 1) {
        return f(l, r - 1) + h(l, r);
    }
    else {
        return 3 * f(l / 2, r / 2);
    }
}

int main() {
    int t;
    cin >> t;
    while(t--) {
        int l, r;
        cin >> l >> r;
        cout << f(l, r + 1) << endl;
    }
    return 0;
}