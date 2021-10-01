// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// T: O(h)
// S: O(1)
class Solution {
public:
    TreeNode* deleteNode(TreeNode* root, int key) {
        if (!root) return root;
        
        if (root->val < key) {
            root->right = deleteNode(root->right, key);
            return root;
        } 
        if (root->val > key) {
            root->left = deleteNode(root->left, key);
            return root;
        }
        
        // root->val == key
        TreeNode* new_root;
        if (root->left && root->right) {
            TreeNode* parent = root;
            new_root = root->right;
            while (new_root->left) {
                parent = new_root;
                new_root = new_root->left;
            }
            // now new_root is the most left node of the right subtree of root
            // swap root and new_root
            // here can recursively delete right subtree after swapping
            // or finish all the operations which will simplify the code and reduce time
            if (parent != root) {
                parent->left = new_root->right;
                new_root->right = root->right;
            }
            new_root->left = root->left;
        } else {
            if (!root->left)
                new_root = root->right;
            else
                new_root = root->left;
        }
        
        delete root;
        return new_root;
    }
};