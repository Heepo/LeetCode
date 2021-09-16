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
    // T: O(nlogn) searching right most node of the left subtree will cost O(logn) for n nodes
    // S: O(1) only uses a pointer to store the right child which needs to be reallocated
    void flatten(TreeNode* root) {
        if (!root) return;
        if (!root->left && !root->right) return;
        
        TreeNode* cur = root;
        // always appends the right child to the right most node of the left subtree
        while (cur) {
            if (!cur->left) {
                cur = cur->right;
                continue;
            }
            // skip the searching for the right most node of the left subtree, which would cost O(n) in the worst case
            if (!cur->right) {
                cur->right = cur->left;
                cur->left = nullptr;
                cur = cur->right;
                continue;
            }
            
            TreeNode* right_most_of_left = cur->left;
            while (right_most_of_left->right) right_most_of_left = right_most_of_left->right;
            right_most_of_left->right = cur->right;
            
            cur->right = cur->left;
            cur->left = nullptr;
            cur = cur->right;
        }
        
        return;
    }
};