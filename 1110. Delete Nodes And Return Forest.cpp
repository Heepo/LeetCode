#include <vector>
#include <unordered_set>
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

class Solution {
public:
    vector<TreeNode*> delNodes(TreeNode* root, vector<int>& to_delete) {
        if (!root) return {};
        if (to_delete.empty()) return {root};
        
        vector<TreeNode*> ans;
        unordered_set<int> s_;
        for (auto node: to_delete) s_.insert(node);

        root = del_nodes(root, s_, ans);
        // check if root has been deleted
        if (root) ans.push_back(root);
        
        return ans;
    }
    
    TreeNode* del_nodes(TreeNode* cur, unordered_set<int>& s_, vector<TreeNode*>& ans) {
        if (!cur) return cur;
        
        // post order traversal to deal with children first
        cur->left = del_nodes(cur->left, s_, ans);
        cur->right = del_nodes(cur->right, s_, ans);
        
        // deals with self
        if (s_.count(cur->val)) {
            // if cur->left needs to be deleted, then it has been set to nullptr
            if (cur->left) ans.push_back(cur->left);
            if (cur->right) ans.push_back(cur->right);
            delete cur;
            
            return nullptr;
        }
        
        return cur;
    }
};