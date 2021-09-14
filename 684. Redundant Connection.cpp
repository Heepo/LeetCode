#include <vector>
using namespace std;

// T: amortized O(n)
class Union {
public:
    // the given edges num is equal with the nodes num
    Union(int n) {
        parents = vector<int>(n+1, 0);
        ranks = vector<int>(n+1, 0);
        
        for (int i = 0; i <= n; i++) parents[i] = i;
    }
    
    void build_union(vector<vector<int>>& edges) {
        for (auto edge: edges) {
            int pu = find(edge[0]);
            int pv = find(edge[1]);
            // already in the same cluster
            if (pu == pv) return;
            
            merge(pu, pv);
        }
    }
    
    // if nodes of the edge are already in the same cluster, returns true
    bool union_edge(vector<int>& edge) {
        int pu = find(edge[0]);
        int pv = find(edge[1]);

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
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        Union u_ = Union(edges.size());
  
        for (auto edge: edges)
            if (u_.union_edge(edge)) return edge;
        
        return {};
    }
};