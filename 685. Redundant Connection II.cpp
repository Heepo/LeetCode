#include <vector>
using namespace std;

// T: amortized O(n), O(nlog*n)
class Union {
public:
    // the given edges num is equal with the nodes num
    Union(int n) {
        clusters = vector<int>(n+1, 0);
        parents = vector<int>(n+1, 0);
        sizes = vector<int>(n+1, 1);
        
        for (int i = 0; i <= n; i++) clusters[i] = i;
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
    
    vector<int> findDirectedRedundant(vector<vector<int>>& edges) {
        vector<int> ans;
        
        // used when there is more than one parent for same node
        // both are candidates
        vector<int> ans1;
        vector<int> ans2;
        // first scan to find if there are any node has more than one parent.
        // if found, then the answer must be one of them
        for (auto& edge: edges) {
            if (parents[edge[1]] > 0) {
                ans1 = {parents[edge[1]], edge[1]};
                ans2 = {edge[0], edge[1]};
                // delete this edge
                edge[0] = edge[1] = -1;
            } else
                parents[edge[1]] = edge[0];
        }
        
        // second round scan
        // if ans1 && ans2 are empty, just removes the last edge makes a circle.
        for (auto edge: edges) {
            if (edge[0] == -1) continue;
            
            int pu = find(edge[0]);
            int pv = find(edge[1]);
            
            if (pu == pv) {
                // ans1 should be the result
                if (!ans1.empty()) return ans1;
                
                return edge;
            }
            merge(pu, pv);
        }
        
        // if comes here, second round scan found no circle, then ans2 is the redundant
        return ans2;
    }
    
    // low sizes cluster will be merged to large sizes cluster to reduce the update operations
    void merge(int u, int v) {
        if (sizes[u] > sizes[v]) {
            sizes[clusters[v]] -= sizes[v];
            clusters[v] = u;
            sizes[u] += sizes[v];
            return;
        }
        
        sizes[clusters[u]] -= sizes[u];
        clusters[u] = v;
        sizes[v] += sizes[u];
        
        return;
    }
    
    // lazily makes the tree as flat as possible
    // T: amortized O(1) (O(log*n))
    int find(int u) {
        // lazy path compression -> reduce the time cost of finding root
        if (clusters[u] != u) {
            sizes[clusters[u]] -= sizes[u];
            int v = find(clusters[u]);
            sizes[v] += sizes[u];
            clusters[u] = v;
        }

        return clusters[u];
    }

private:
    vector<int> clusters;
    vector<int> parents;
    // small sizes node will be merged to large sizes node's children to reduce the time cost of finding root
    // sizes represent the node counts of each subtree
    vector<int> sizes;
};


// 1. no circle allowed
// 2. each node can't have more than one parent
// removes connection to another parent does not always satisfy the conditions.
// because the later might only connect to this node, once the connection is removed, the node can't be include to the tree
class Solution {
public:
    vector<int> findRedundantDirectedConnection(vector<vector<int>>& edges) {
        Union union_(edges.size());
        
        return union_.findDirectedRedundant(edges);
    }
};