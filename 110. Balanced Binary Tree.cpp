#include <algorithm>
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
    bool isBalanced(TreeNode* root) {
        if (!root) return true;
        
        // int height = 0;
        // return dfs_(root, height);

        bool isBalanced = true;
        height_(root, isBalanced);
        
        return isBalanced;
    }
    
private:
    int height_(TreeNode* curr, bool& isBalanced) {
        if (!curr) return -1;
        
        int l_height = height_(curr->left, isBalanced);
        int r_height = height_(curr->right, isBalanced);
        if (abs(l_height - r_height) > 1) isBalanced = false;
        
        return max(l_height, r_height) + 1;
    }

    bool dfs_(TreeNode* curr, int& height) {
        if (!curr) {
            height = 0;
            
            return true;
        }
        
        bool is_balanced = dfs_(curr->left, height);
        if (!is_balanced) return false;
        int l = height;
        
        is_balanced = dfs_(curr->right, height);
        if (!is_balanced) return false;
        int r = height;
        
        height = max(l, r) + 1;
        if (abs(l - r) <= 1) return true;
        
        return false;
    }
};