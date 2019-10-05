import java.util.Arrays;
import java.util.Scanner;

public class cf1228B {
    private static int solve() {
        Scanner in = new Scanner(System.in);
        int h = in.nextInt();
        int w = in.nextInt();
        int[][] board = new int[h][w];
        for(int i = 0; i < h; i++) {
            Arrays.fill(board[i], -1);
        }
        for(int i = 0; i < h; i++) {
            int r = in.nextInt();
            Arrays.fill(board[i], 0, r, 1);
            if(r < w) {
                board[i][r] = 0;
            }
        }
        for(int j = 0; j < w; j++) {
            int c = in.nextInt();
            for(int i = 0; i < c; i++) {
                if(board[i][j] == 0) {
                    return 0;
                }
                board[i][j] = 1;
            }
            if(c < h) {
                if(board[c][j] == 1) {
                    return 0;
                }
                board[c][j] = 0;
            }
        }
        final int MOD = (int)1e9 + 7;
        int ans = 1;
        for(int i = 0; i < h; i++) {
            for(int j = 0; j < w; j++) {
                if(board[i][j] == -1) {
                    ans *= 2;
                    ans %= MOD;
                }
            }
        }
        return ans;
    }
    public static void main(String[] args) {
        System.out.println(solve());
    }
}
