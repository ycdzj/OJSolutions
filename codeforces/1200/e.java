package OJSolutions;

import java.util.Scanner;

public class cf_1200E {
    static class StringHash {
        static final int MOD = (int)1e9 + 7;
        static final int STEP = 107;
        static int addmod(int a, int b) { return (a + b) % MOD; }
        static int mulmod(long a, int b) { return (int)((a * b) % MOD); }

        int hash, len, mul = 1;
        void addFront(int c) {
            hash = addmod(hash, mulmod(mul, c));
            len++;
            mul = mulmod(mul, STEP);
        }
        void addBack(int c) {
            hash = addmod(mulmod(hash, STEP), c);
            len++;
            mul = mulmod(mul, STEP);
        }
    }
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);

        int n = in.nextInt();
        StringBuilder cur = new StringBuilder();
        for(int i = 0; i < n; i++) {
            String str = in.next();
            int len = Math.min(str.length(), cur.length());
            StringHash s = new StringHash(), t = new StringHash();
            int maxLen = 0;
            for(int j = 0; j < len; j++) {
                s.addFront(cur.charAt(cur.length() - 1 - j));
                t.addBack(str.charAt(j));
                if(s.hash == t.hash) {
                    maxLen = j + 1;
                }
            }
            for(int j = maxLen; j < str.length(); j++) {
                cur.append(str.charAt(j));
            }
        }
        System.out.println(cur);
    }
}
