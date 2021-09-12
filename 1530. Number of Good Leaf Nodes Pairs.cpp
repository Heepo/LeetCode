
#include <unordered_map>
using namespace std;

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
// T: O(|leaves|^2*d) -> O(n^2*d), S: O(n)
class Solution1 {
public:
    int countPairs(TreeNode* root, int distance) {
        if (!root) return 0;
        unordered_map<TreeNode*, TreeNode*> parent_map;
        vector<TreeNode*> leaves;
        dfs(root, nullptr, leaves, parent_map);
        
        int ans = 0;
        unordered_map<TreeNode*, int> parent_distance;
        auto isGood = [&](TreeNode* leaf2) -> bool {
            for (int i = 0; i < distance && leaf2; i++, leaf2=parent_map[leaf2]) {
                if (parent_distance.count(leaf2) && i + parent_distance[leaf2] <= distance) return true;
            }
            return false;
        };
        
        for (int i = 0; i < leaves.size(); i++) {
            parent_distance.clear();
            TreeNode* p = leaves[i];
            int d = 0;
            while (parent_map[p] && d < distance) {
                parent_distance[parent_map[p]] = ++d;
                p = parent_map[p];
            }
            for (int j = i + 1; j < leaves.size(); j++) {
                if (isGood(leaves[j])) ans++;
            }
        }
        
        return ans;
    }
    
    void dfs(TreeNode* c, TreeNode* p, vector<TreeNode*>& leaves, unordered_map<TreeNode*, TreeNode*>& parent_map) {
        if (!c) return;
        parent_map[c] = p;
        
        if (c->left) dfs(c->left, c, leaves, parent_map);
        if (c->right) dfs(c->right, c, leaves, parent_map);
        
        if (!c->left && !c->right) leaves.push_back(c);
     
        return;
    }
};
class Solution2 {
public:
    // T: O(n*d^2), S:O(d+logn)
    int countPairs(TreeNode* root, int distance) {
        if (!root) return 0;
        
        int ans = 0;
        // the quest limits the distance to 1-10
        // returns the number of leaves which has the same distance to root then uses DP by dfs
        vector<int> dist_num_m = dfs(root, distance, ans);
        return ans;
    }
    
    vector<int> dfs(TreeNode* cur, int distance, int& ans) {
        vector<int> v(distance+1, 0);
        if (!cur) {
            v[0] = 0;
            return v;
        }
        if (!cur->left && !cur->right) {
            v[0] = 1;
            return v;
        }
        
        vector<int> l_v;
        vector<int> r_v;
        l_v = dfs(cur->left, distance, ans);
        r_v = dfs(cur->right, distance, ans);
        for (int i = 1; i <= distance; i++) {
            v[i] = l_v[i-1] + r_v[i-1];
        }
        for (int i = 0; i <= distance; i++) {
            for (int j = 0; j <= distance; j++) {
                if (i + j + 2 <= distance) ans += l_v[i] * r_v[j];
            }
        }
        
        return v;
    }
};