import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class cf1228D {
    static class Graph {
        private int n, m;
        private List<Integer>[] adj;
        public Graph(int n, int m) {
            this.n = n;
            this.m = m;
            adj = new List[n];
            for(int i = 0; i < n; i++) {
                adj[i] = new ArrayList<>();
            }
        }
        public int getN() {
            return n;
        }
        public int getM() {
            return m;
        }
        public void addEdge(int u, int v) {
            adj[u].add(v);
        }
        public void solve() {
            boolean[] vis = new boolean[n];
            int[] ans = new int[n];
            int cnt = 0;
            for(int i = 0; i < n; i++) {
                if(!vis[i]) {
                    if(cnt++ == 3) {
                        System.out.println(-1);
                        return;
                    }
                    boolean[] curvis = new boolean[n];
                    for(int v : adj[i]) {
                        curvis[v] = true;
                    }
                    for(int j = 0; j < n; j++) {
                        if(!curvis[j]) {
                            vis[j] = true;
                            ans[j] = cnt;
                            if(adj[j].size() != adj[i].size()) {
                                System.out.println(-1);
                                return;
                            }
                            for(int v : adj[j]) {
                                if(!curvis[v]) {
                                    System.out.println(-1);
                                    return;
                                }
                            }
                        }
                    }
                }
            }
            if(cnt != 3) {
                System.out.println(-1);
                return;
            }
            for(int i = 0; i < n; i++) {
                System.out.print(ans[i] + " ");
            }
            System.out.println();
        }

    }
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        Graph graph = new Graph(in.nextInt(), in.nextInt());
        for(int i = 0; i < graph.getM(); i++) {
            int u = in.nextInt() - 1;
            int v = in.nextInt() - 1;
            graph.addEdge(u, v);
            graph.addEdge(v, u);
        }
        graph.solve();
    }
}
