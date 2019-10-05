import java.util.Scanner;

public class cf1228C {
    private static boolean[] getPrime(int n) {
        boolean[] res = new boolean[n];
        res[0] = res[1] = true;
        for(int i = 2; i < n; i++) {
            if(!res[i]) {
                for(int j = i * 2; j < n; j += i) {
                    res[j] = true;
                }
            }
        }
        return res;
    }
    private static final long MOD = (int)1e9 + 7;
    private static long qpow(int a, long x) {
        long res = 1, cur = a;
        while(x != 0) {
            if((x & 1) == 1) {
                res *= cur;
                res %= MOD;
            }
            cur *= cur;
            cur %= MOD;
            x >>= 1;
        }
        return res;
    }
    private static long f(int p, long n) {
        long cnt = 0;
        long cur = 1;
        do {
            cur *= p;
            cnt += n / cur;
        } while(cur <= n / p);
        return qpow(p, cnt);
    }
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int x = in.nextInt();
        long n = in.nextLong();

        boolean notPrime[] = getPrime((int)Math.sqrt(x) + 5);
        long ans = 1;
        for(int i = 2; i < notPrime.length; i++) {
            if(!notPrime[i] && x % i == 0) {
                ans *= f(i, n);
                ans %= MOD;
                while(x % i == 0) {
                    x /= i;
                }
            }
        }
        if(x > 1) {
            ans *= f(x, n);
            ans %= MOD;
        }
        System.out.println(ans);
    }
}
