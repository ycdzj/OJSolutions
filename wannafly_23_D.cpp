#include <cstdio>
const int MAXN = 35;
const double eps = 1e-10;
int dcmp(double x) {
	if(-eps <= x && x <= eps) return 0;
	return x < 0 ? -1 : 1;
}
int r, c;
double mat[MAXN][MAXN];
bool vis[MAXN];
int rank() {
	int res = 0;
	for(int j = 0; j < c; j++) {
		for(int i = 0; i < r; i++) if(!vis[i] && dcmp(mat[i][j]) != 0) {
			vis[i] = true;
			for(int ii = 0; ii < r; ii++) if(ii != i && dcmp(mat[ii][j]) != 0) {
					double slope = mat[ii][j] / mat[i][j];
					for(int jj = 0; jj < c; jj++) mat[ii][jj] -= slope * mat[i][jj];
				}
			res++;
			break;
		}
	}
	return res;
}
int main() {
	scanf("%d%d", &r, &c);
	for(int i = 0; i < r; i++) for(int j = 0; j < c; j++) scanf("%lf", &mat[i][j]);
	int rk = rank();
	if(rk == 0) rk = 1;
	printf("%d\n", rk * (r + c));
	return 0;
}