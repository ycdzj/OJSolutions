package OJSolutions;

import java.util.ArrayDeque;
import java.util.Queue;
import java.util.Scanner;

public class cf_1202E {
    static class ACA {
        static class Node {
            Node next[], fail;
            int end;
            Node() {
                next = new Node[26];
            }
        }
        Node root;
        ACA() {
            root = new Node();
        }
        void insert(String str, int len) {
            Node cur = root;
            for(int i = 0; i < len; i++) {
                int ch = str.charAt(i) - 'a';
                if(cur.next[ch] == null) {
                    cur.next[ch] = new Node();
                }
                cur = cur.next[ch];
            }
            cur.end++;
        }
        void build() {
            Queue<Node> que = new ArrayDeque<>();
            root.fail = root;
            for(int i = 0; i < 26; i++) {
                if(root.next[i] == null) {
                    root.next[i] = root;
                }
                else {
                    root.next[i].fail = root;
                    que.add(root.next[i]);
                }
            }
            while(!que.isEmpty()) {
                Node u = que.poll();
                u.end += u.fail.end;
                for(int i = 0; i < 26; i++) {
                    if(u.next[i] == null) {
                        u.next[i] = u.fail.next[i];
                    }
                    else {
                        u.next[i].fail = u.fail.next[i];
                        que.add(u.next[i]);
                    }
                }
            }
        }
    }
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);

        String t = in.next();
        int n = in.nextInt();
        String v[] = new String[n];
        int cnt[] = new int[t.length()];
        ACA aca = new ACA();

        for(int i = 0; i < n; i++) {
            v[i] = in.next();
            aca.insert(v[i], v[i].length());
        }
        aca.build();
        ACA.Node cur = aca.root;
        for(int i = 0; i < t.length(); i++) {
            cur = cur.next[t.charAt(i) - 'a'];
            cnt[i] = cur.end;
        }

        long ans = 0;
        aca = new ACA();
        for(int i = 0; i < n; i++) {
            aca.insert(new StringBuilder(v[i]).reverse().toString(), v[i].length());
        }
        aca.build();
        cur = aca.root;
        for(int i = t.length() - 1; i >= 1; i--) {
            cur = cur.next[t.charAt((i)) - 'a'];
            ans += (long)cnt[i - 1] * cur.end;
        }

        System.out.println(ans);
    }
}
