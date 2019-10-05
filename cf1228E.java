import java.util.Scanner;

public class cf1228E {
    static class Mod {
        public static final int MOD = (int)1e9 + 7;
        public static int add(int a, int b) {
            return (a + b) % MOD;
        }
        public static int mul(long a, int b) {
            return (int)((a * b) % MOD);
        }
        public static int pow(int a, int x) {
            int res = 1;
            while(x != 0) {
                if((x & 1) == 1) {
                    res = mul(res, a);
                }
                x >>= 1;
                a = mul(a, a);
            }
            return res;
        }
    }
    static class Combinator {
        int[] factor, invFactor;
        public Combinator(int n) {
            factor = new int[n + 1];
            invFactor = new int[n + 1];
            factor[0] = 1;
            for(int i = 1; i <= n; i++) {
                factor[i] = Mod.mul(factor[i - 1], i);
            }
            invFactor[n] = Mod.pow(factor[n], Mod.MOD - 2);
            for(int i = n - 1; i >= 0; i--) {
                invFactor[i] = Mod.mul(invFactor[i + 1], i + 1);
            }
        }
        public int calc(int n, int m) {
            return Mod.mul(factor[n], Mod.mul(invFactor[m], invFactor[n - m]));
        }
    }
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int n = in.nextInt(), k = in.nextInt();
        Combinator combine = new Combinator(n);
        int[][] f = new int[n + 1][n + 1];
        f[0][0] = 1;
        for(int i = 1; i <= n; i++) {
            for(int j = 0; j <= n; j++) {
                int powK = 1;
                for(int x = 0; x <= j; x++) {
                    int cur = f[i - 1][x];
                    cur = Mod.mul(cur, powK);
                    cur = Mod.mul(cur, combine.calc(n - x, j - x));
                    f[i][j] = Mod.add(f[i][j], cur);
                    powK = Mod.mul(powK, k);
                }
            }
            int powKMinusOne = 1;
            for(int j = n; j >= 0; j--) {
                f[i][j] = Mod.mul(f[i][j], powKMinusOne);
                if(j > 0) {
                    powKMinusOne = Mod.mul(powKMinusOne, k - 1);
                }
            }
            for(int j = 0; j <= n; j++) {
                f[i][j] = Mod.add(f[i][j], Mod.MOD - Mod.mul(f[i - 1][j], powKMinusOne));
            }
        }
        System.out.println(f[n][n]);
    }
}
