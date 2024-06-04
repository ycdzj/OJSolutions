package OJSolutions;

import java.util.Scanner;

public class cf_1200EKmp {
    static int[] getNext(String str) {
        int len = str.length();
        int next[] = new int[len];
        next[0] = 0;
        for(int i = 1; i < len; i++) {
            int cur = next[i - 1];
            while(cur > 0 && str.charAt(cur) != str.charAt(i)) {
                cur = next[cur - 1];
            }
            if(str.charAt(cur) == str.charAt(i)) {
                cur++;
            }
            next[i] = cur;
        }
        return next;
    }
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);

        int n = in.nextInt();
        StringBuilder cur = new StringBuilder();

        for(int i = 0; i < n; i++) {
            String str = in.next();
            int len = Math.min(str.length(), cur.length());
            String tmp = str + '#' + cur.substring(cur.length() - len);
            int maxLen = getNext(tmp)[tmp.length() - 1];
            cur.append(str.substring(maxLen));
        }

        System.out.println(cur);
    }
}
