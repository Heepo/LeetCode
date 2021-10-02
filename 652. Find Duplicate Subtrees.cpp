#include <vector>
#include <unordered_map>
#include <string>
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

// serializes every subtree and counts it in a hashtable
// T: O(n^2)
// S: O(n^2)
class Solution {
public:
    vector<TreeNode*> findDuplicateSubtrees(TreeNode* root) {
        if (!root) return {};
        
        vector<TreeNode*> ans;
        unordered_map<std::string, int> count;
        serialize_(root, count, ans);
        
        return ans;
    }
    
private:
    std::string serialize_(TreeNode* cur, unordered_map<std::string, int>& count, vector<TreeNode*>& ans) {
        if (!cur) return "#";
        
        // O(n)
        std::string key = std::to_string(cur->val) + "," + serialize_(cur->left, count, ans) + "," + serialize_(cur->right, count, ans);
        
        if (++count[key] == 2) ans.push_back(cur);
        
        return key;
    }
};


// T: O(n)
// S: O(n)
class Solution2 {
public:
    vector<TreeNode*> findDuplicateSubtrees(TreeNode* root) {
        if (!root) return {};
        
        vector<TreeNode*> ans;
        unordered_map<long, int> id_m;
        unordered_map<int, int> id_count;
        assign_id_(root, id_m, id_count, ans);
        
        return ans;
    }
    
private:
    int assign_id_(TreeNode* cur, unordered_map<long, int>& id_m, unordered_map<int, int>& id_count, vector<TreeNode*>& ans) {
        if (!cur) return 0;
        
        // traversal time O(n), id assignment O(1)
        // Assuming the unique node number is under 65536
        long key = (static_cast<long>(static_cast<unsigned int>(cur->val)) << 32) | (assign_id_(cur->left, id_m, id_count, ans) << 16) | assign_id_(cur->right, id_m, id_count, ans);
        int id = id_m.count(key) ? id_m[key] : (id_m.size() + 1);
        id_m[key] = id;
        
        if (++id_count[id] == 2) ans.push_back(cur);
        
        return id;
    }
};