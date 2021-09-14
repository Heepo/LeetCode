#include <vector>
#include <algorithm>
using namespace std;

class TreeAncestor {
public:
    // If uses a matrix to record every node's path, in the worst case the construction time would be O(n^2)  which won't pass
    // Only records the 2^i-th parents, then the construction time will reduce to O(nlogn)
    TreeAncestor(int n, vector<int>& parent) {
        g_ = vector<vector<int>>(n, vector<int>{});
        ancestors_ = vector<vector<int>>(n, vector<int>{});     
        for (int i = 0; i < parent.size(); i++) {
            if (parent[i] != -1) {
                g_[parent[i]].push_back(i);
            }
        }
        vector<int> path;
        path.reserve(n);
        dfs(0, path);
    }
    
    // uses bit composing to do query processing, query time O(log(min_(k, n)))
    // Noted that, the constuction is one-time job, so when query multiple times(>> n) then the time consuming will be dominated
    // by query process. Here the query number of times is at the same magnitude of n
    int getKthAncestor(int node, int k) {
        if (k == 0) return node;
        if (node == 0 && k > 0) return -1;
        
        // get the highest bit postion, started from 0 and increasing from right to left
        // gcc builtin function of counting leading zeros
        // int highest_bit_pos = 31 - __builtin_clz(k);
        int highest_bit_pos = 0;
        int tmp = k;
        while (tmp >>= 1) highest_bit_pos++;
        tmp = min(highest_bit_pos, int(ancestors_[node].size() - 1));
        return getKthAncestor(ancestors_[node][tmp], k - (1 << tmp));
    }
    
private:
    // the ajacent list form of the tree and used for traversal
    vector<vector<int>> g_;    
    vector<vector<int>> ancestors_;
    
    void dfs(int node, vector<int>& path) {     
        // T & S of construction 2^i-th ancestors vector: O(logn)
        for (int offset = 1; offset <= path.size(); offset *= 2) {
            // the nearest are the left
            ancestors_[node].push_back(path[path.size() - offset]);
            //std::cout << "node: " << node << " ancestors_ push back: " << ancestors_[node].back() << std::endl;
        }
        
        path.push_back(node);
        for (auto child: g_[node])
            dfs(child, path);
        path.pop_back();
        
        return;
    }
};

/**
 * Your TreeAncestor object will be instantiated and called as such:
 * TreeAncestor* obj = new TreeAncestor(n, parent);
 * int param_1 = obj->getKthAncestor(node,k);
 */