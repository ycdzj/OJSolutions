#include <iostream>
using namespace std;

int main() {
    int t;
    cin >> t;
    while(t--) {
        int b, p, f, h, c;
        cin >> b >> p >> f >> h >> c;
        if(h < c) {
            swap(h, c);
            swap(p, f);
        }
        int ham = min(b / 2, p);
        b -= 2 * ham;
        int chk = min(b / 2, f);
        cout << h * ham + c * chk << endl;
    }
    return 0;
}
