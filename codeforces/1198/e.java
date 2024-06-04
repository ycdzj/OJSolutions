package OJSolutions;

import java.util.*;

public class cf_1198E {
    static class WeightedGraph {
        static class Edge {
            int v, w;
            Edge rev;
            Edge(int v, int w) {
                this.v = v;
                this.w = w;
            }
        }
        List<Edge>[] adj;
        WeightedGraph(int n) {
            adj = new ArrayList[n];
            for(int i = 0; i < n; i++) {
                adj[i] = new ArrayList<>();
            }
        }
        void addEdge(int u, int v, int w) {
            adj[u].add(new Edge(v, w));
        }
    }
    static class Dinic extends WeightedGraph {
        int level[], cur[];
        Dinic(int n) {
            super(n);
            level = new int[n];
            cur = new int[n];
        }
        void addEdge(int u, int v, int cap) {
            Edge x = new Edge(v, cap);
            Edge y = new Edge(u, 0);
            x.rev = y;
            y.rev = x;
            adj[u].add(x);
            adj[v].add(y);
        }
        boolean dinicBfs(int s, int t) {
            Arrays.fill(level, -1);
            Queue<Integer> que = new ArrayDeque<>();

            level[s] = 0;
            cur[s] = 0;
            que.add(s);

            while(!que.isEmpty()) {
                int u = que.poll();
                if(u == t) return true;
                for(int i = 0; i < adj[u].size(); i++) {
                    Edge e = adj[u].get(i);
                    if(e.w > 0 && level[e.v] == -1) {
                        level[e.v] = level[u] + 1;
                        cur[e.v] = 0;
                        que.add(e.v);
                    }
                }
            }
            return false;
        }
        int dinicDfs(int u, int curMin, int t) {
            if(u == t) return curMin;
            if(level[u] >= level[t]) return 0;

            int res = 0;
            for(; curMin > 0 && cur[u] < adj[u].size(); cur[u]++) {
                Edge e = adj[u].get(cur[u]);
                if(e.w > 0 && level[e.v] == level[u] + 1) {
                    int nxtMin = Math.min(curMin, e.w);
                    int x = dinicDfs(e.v, nxtMin, t);
                    curMin -= x;
                    e.w -= x;
                    e.rev.w += x;
                    res += x;
                }
            }
            return res;
        }
        int dinic(int s, int t) {
            int res = 0;
            while(dinicBfs(s, t)) {
                res += dinicDfs(s, Integer.MAX_VALUE, t);
            }
            return res;
        }
    }
    static class Rectangle {
        int x1, y1, x2, y2;
        Rectangle(int x1, int y1, int x2, int y2) {
            this.x1 = x1;
            this.y1 = y1;
            this.x2 = x2;
            this.y2 = y2;
        }
    }
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int n = in.nextInt(), m = in.nextInt();
        Rectangle[] rectangles = new Rectangle[m];
        HashSet<Integer> x = new HashSet<>(), y = new HashSet<>();
        for(int i = 0; i < m; i++) {
            rectangles[i] = new Rectangle(in.nextInt(), in.nextInt(), in.nextInt(), in.nextInt());
            x.add(rectangles[i].x1);
            x.add(rectangles[i].x2 + 1);
            y.add(rectangles[i].y1);
            y.add(rectangles[i].y2 + 1);
        }
        ArrayList<Integer> xArr = new ArrayList<>(x);
        ArrayList<Integer> yArr = new ArrayList<>(y);
        Collections.sort(xArr);
        Collections.sort(yArr);
        Dinic dinicGraph = new Dinic(xArr.size() + yArr.size() + 2);
        for(int i = 0; i < m; i++) {
            int u = Collections.binarySearch(xArr, rectangles[i].x1);
            int s = Collections.binarySearch(yArr, rectangles[i].y1);
            for(; xArr.get(u) != rectangles[i].x2 + 1; u++) {
                for(int v = s; yArr.get(v) != rectangles[i].y2 + 1; v++) {
                    dinicGraph.addEdge(u, xArr.size() + v, Integer.MAX_VALUE);
                }
            }
        }
        int s = xArr.size() + yArr.size();
        int t = s + 1;
        for(int i = 0; i < xArr.size() - 1; i++) {
            dinicGraph.addEdge(s, i, xArr.get(i + 1) - xArr.get(i));
        }
        for(int i = 0; i < yArr.size() - 1; i++) {
            dinicGraph.addEdge(xArr.size() + i, t, yArr.get(i + 1) - yArr.get(i));
        }
        System.out.println(dinicGraph.dinic(s, t));
    }
}
