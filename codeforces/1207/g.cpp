#include <iostream>
#include <vector>
#include <list>
#include <cstring>
#include <queue>
using namespace std;

struct TrieNode {
    int end;
    TrieNode* next[26];
    TrieNode* fail;
    int lIdx, rIdx;
    vector<TrieNode*> failAdj;
    TrieNode() {
        end = 0;
        fail = 0;
        memset(next, 0, sizeof(next));
    }
};
struct Trie {
    list<TrieNode> nodes;
    TrieNode* root;
    TrieNode* newTrieNode() {
        nodes.emplace_back();
        return &(nodes.back());
    }
    Trie() {
        root = newTrieNode();
    }
    TrieNode* insert(const char *str, int len) {
        TrieNode *u = root;
        for(int i = 0; i < len; i++) {
            int ch = str[i] - 'a';
            if(u->next[ch] == 0) {
                u->next[ch] = newTrieNode();
            }
            u = u->next[ch];
        }
        u->end++;
        return u;
    }
    void build() {
        root->fail = root;
        queue<TrieNode*> que;
        for(int i = 0; i < 26; i++) {
            if(root->next[i] == 0) {
                root->next[i] = root;
            }
            else {
                root->next[i]->fail = root;
                que.push(root->next[i]);
            }
        }
        while(!que.empty()) {
            TrieNode* u = que.front();
            que.pop();
            for(int i = 0; i < 26; i++) {
                if(u->next[i] == 0) {
                    u->next[i] = u->fail->next[i];
                }
                else {
                    u->next[i]->fail = u->fail->next[i];
                    que.push(u->next[i]);
                }
            }
        }
    }
    int curIdx;
    void buildIdxDfs(TrieNode *u) {
        u->lIdx = curIdx++;
        for(auto node : u->failAdj) {
            buildIdxDfs(node);
        }
        u->rIdx = curIdx++;
    }
    void buildIdx() {
        for(auto &node : nodes) {
            if(&node == root) {
                continue;
            }
            node.fail->failAdj.push_back(&node);
        }
        curIdx = 1;
        buildIdxDfs(root);
    }
};

struct Edge {
    int v;
    char ch;
};
struct Graph {
    int n;
    vector<vector<Edge>> adj;
    vector<vector<pair<TrieNode*, int*>>> query;
    Graph(int n_)
            : n(n_) {
        adj.resize(n);
        query.resize(n);
    }
    void addEdge(int u, int v, char ch) {
        adj[u].push_back({v, ch});
    }
};

struct BIT {
    int n;
    vector<int> tree;

    int lowbit(int x) {
        return x & (-x);
    }
    void init(int n_) {
        n = n_;
        tree.resize(n + 1);
    }
    void change(int p, int val) {
        while(p <= n) {
            tree[p] += val;
            p += lowbit(p);
        }
    }
    int query(int p) {
        int res = 0;
        while(p >= 1) {
            res += tree[p];
            p -= lowbit(p);
        }
        return res;
    }
} bit;
void dfs(Graph &graph, int u, TrieNode* curTrie) {
    bit.change(curTrie->lIdx, 1);
    for(auto pr : graph.query[u]) {
        *(pr.second) = bit.query(pr.first->rIdx) - bit.query(pr.first->lIdx - 1);
    }
    for(auto edge : graph.adj[u]) {
        dfs(graph, edge.v, curTrie->next[edge.ch - 'a']);
    }
    bit.change(curTrie->lIdx, -1);
}
int main() {
    ios::sync_with_stdio(false);
    int n;
    cin >> n;
    Graph graph(n + 1);
    for(int i = 1; i <= n; i++) {
        int t;
        cin >> t;
        if(t == 1) {
            string ch;
            cin >> ch;
            graph.addEdge(0, i, ch[0]);
        }
        else {
            int par;
            string ch;
            cin >> par >> ch;
            graph.addEdge(par, i, ch[0]);
        }
    }
    int m;
    cin >> m;
    Trie trie;
    vector<int> ans(m);
    for(int i = 0; i < m; i++) {
        int u;
        string str;
        cin >> u >> str;
        graph.query[u].push_back({trie.insert(str.c_str(), str.length()), &ans[i]});
    }
    trie.build();
    trie.buildIdx();
    bit.init(trie.curIdx);
    dfs(graph, 0, trie.root);
    for(int i = 0; i < m; i++) {
        cout << ans[i] << endl;
    }
    return 0;
}
