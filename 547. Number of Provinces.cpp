#include <vector>
#include <unordered_set>
using namespace std;

// T: amortized O(n)
class UnionFind {
public:
    // the given edges num is equal with the nodes num
    UnionFind(int n) {
        parents = vector<int>(n+1, 0);
        ranks = vector<int>(n+1, 0);
        
        for (int i = 0; i <= n; i++) parents[i] = i;
    }
    
    void union_edges(vector<vector<int>>& edges) {
        for (auto edge: edges) {
            int pu = find(edge[0]);
            int pv = find(edge[1]);
            // already in the same cluster
            if (pu == pv) return;
            
            merge(pu, pv);
        }
    }
    
    // if nodes of the edge are already in the same cluster, returns true
    bool union_edge(int u, int v) {
        int pu = find(u);
        int pv = find(v);

        if (pu == pv) return true;
        merge(pu, pv);
        return false;
    }
    
    void merge(int u, int v) {
        if (ranks[u] < ranks[v])
            parents[u] = v;
        else if (ranks[u] > ranks[v])
            parents[v] = u;
        else
            // only place that append one node to be another's child
            parents[u] = v;
            ranks[u]++;
    }
    
    // T: amortized O(1) (O(log*n))
    int find(int u) {
        // path compression -> reduce the time cost of finding root
        if (parents[u] != u) parents[u] = find(parents[u]);
        return parents[u];
    }

private:
    vector<int> parents;
    // low rank node will be merged to high rank node's children to reduce the time cost of finding root
    vector<int> ranks;
};

class Solution {
public:
    int findCircleNum(vector<vector<int>>& isConnected) {
        UnionFind u_ = UnionFind(isConnected.size());
        for (int i = 0; i < isConnected.size(); i++) {
            for (int j = i + 1; j < isConnected[0].size(); j++)
                if (isConnected[i][j] == 1) u_.union_edge(i, j);
        }
        
        unordered_set<int> s_;
        for (int i = 0; i < isConnected.size(); i++)
            s_.insert(u_.find(i));
        
        return s_.size();
    }
};