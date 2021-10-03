// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// in-order traverses over the tree, if the cur->val < prev->val, then it is not a BST
// T: O(n)
// S: O(logn) ~ O(n)
class Solution {
public:
    bool isValidBST(TreeNode* root) {
        if (!root) return true;
        
        prev_ = nullptr;
        return inOrder_(root);
    }

private:
    int* prev_;
    
    bool inOrder_(TreeNode* cur) {
        if (!cur) return true;
        
        if (!inOrder_(cur->left)) return false;
 
        if (prev_ && *prev_ >= cur->val) return false;
        prev_ = &cur->val;
        
        return inOrder_(cur->right);
    }
};