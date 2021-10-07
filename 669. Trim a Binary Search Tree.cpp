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
    // For sanity, it needs to free memory for trimmed nodes
    TreeNode* trimBST(TreeNode* root, int low, int high) {
        if (!root) return nullptr;
        
        if (root->val > high)
            return trimBST(root->left, low, high);
        if (root->val < low)
            return trimBST(root->right, low, high);
        
        root->left = trimBST(root->left, low, root->val);
        root->right = trimBST(root->right, root->val, high);

        return root;
    }
};