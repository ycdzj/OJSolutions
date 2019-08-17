package OJSolutions;

import java.util.Scanner;

public class cf_1190A {
    static class Status {
        long pos, cnt, k;
        long ans;
        Status(long k) {
            this.k = k;
            pos = 0;
            cnt = 0;
            ans = 0;
        }
        void update() {
            if(pos == k) {
                if(cnt > 0) {
                    ans++;
                }
                pos -= cnt;
                cnt = 0;
            }
        }
        void nNonSpecial(long n) {
            long len = Math.min(k - pos, n);
            pos += len;
            n -= len;
            update();
            pos += n;
            pos %= k;
        }
        void oneSpecial() {
            pos++;
            cnt++;
            update();
        }
    }
    static public void main(String[] args) {
        Scanner in = new Scanner(System.in);
        long n = in.nextLong(), m = in.nextLong(), k = in.nextLong();
        long cur = 1;
        Status status = new Status(k);
        for(int i = 0; i < m; i++) {
            long p = in.nextLong();
            status.nNonSpecial(p - cur);
            status.oneSpecial();
            cur = p + 1;
        }
        if(status.cnt > 0) {
            status.ans++;
        }
        System.out.println(status.ans);
    }
}
