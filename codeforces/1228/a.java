import java.util.Scanner;

public class cf1228A {
    private static boolean check(int num) {
        boolean[] vis = new boolean[10];
        while(num != 0) {
            int cur = num % 10;
            if(vis[cur]) {
                return false;
            }
            vis[cur] = true;
            num /= 10;
        }
        return true;
    }
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int l = in.nextInt();
        int r = in.nextInt();
        for(int i = l; i <= r; i++) {
            if(check(i)) {
                System.out.println(i);
                return;
            }
        }
        System.out.println(-1);
    }
}
