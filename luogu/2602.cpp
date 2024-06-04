#include <cstdio>
typedef long long ll;
int cnt[10], digit[15];
ll pow10[15];
ll f[15], sum_f[15];
void solve(ll num, ll *res) {
	int p = 15;
	while(num) {
		digit[--p] = num % 10;
		num /= 10;
	}
	for(int i = 0; i < 10; i++) res[i] = cnt[i] = 0;
	bool flag = false;
	for(int i = p; i < 15; i++) {
		int m = 15 - 1 - i;
		for(int x = 0; x < digit[i]; x++) {
			cnt[x]++;
			for(int j = 0; j < 10; j++) {
				res[j] += pow10[m] * cnt[j];
				if(m > 0) {
					if(j == 0 && x == 0 && !flag) {
						res[j] -= pow10[m] * cnt[j];
						res[j] += sum_f[m - 1] * 9 + 1;
					}
					else {
						res[j] += f[m];
					}
				}
			}
			cnt[x]--;
		}
		if(digit[i] != 0) flag = true;
		cnt[digit[i]]++;
	}
}
ll res_a[10], res_b[10];
int main() {
	pow10[0] = 1;
	for(int i = 1; i < 15; i++) {
		pow10[i] = pow10[i - 1] * 10;
		f[i] = i * pow10[i - 1];
		sum_f[i] = f[i] + sum_f[i - 1];
	}
	ll a, b; scanf("%lld%lld", &a, &b);
	solve(b + 1, res_b);
	solve(a, res_a);
	for(int i = 0; i < 10; i++) printf("%lld%c", res_b[i] - res_a[i], (i + 1 < 10) ? ' ' : '\n');
	return 0;
}