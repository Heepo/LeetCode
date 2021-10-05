#include <vector>
using namespace std;

// T: amortized O(n), O(nlog*n)
class Union {
public:
    // the given edges num is equal with the nodes num
    Union(int n) {
        parents = vector<int>(n+1, 0);
        sizes = vector<int>(n+1, 1);
        
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
    
    // low sizes cluster will be merged to large sizes cluster to reduce the update operations
    void merge(int u, int v) {
        if (sizes[u] > sizes[v]) {
            sizes[parents[v]] -= sizes[v];
            parents[v] = u;
            sizes[u] += sizes[v];
            return;
        }
        
        sizes[parents[u]] -= sizes[u];
        parents[u] = v;
        sizes[v] += sizes[u];
        return;
    }
    
    // lazily makes the tree as flat as possible
    // T: amortized O(1) (O(log*n))
    int find(int u) {
        // lazy path compression -> reduce the time cost of finding root
        if (parents[u] != u) {
            sizes[parents[u]] -= sizes[u];
            int v = find(parents[u]);
            sizes[v] += sizes[u];
            parents[u] = v;
        }
        return parents[u];
    }

private:
    vector<int> parents;
    // small sizes node will be merged to large sizes node's children to reduce the time cost of finding root
    // sizes represent the node counts of each subtree
    vector<int> sizes;
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