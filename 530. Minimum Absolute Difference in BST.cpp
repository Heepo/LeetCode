#include <algorithm>

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// T: O(n)
// S: O(logn) ~ O(n) for stack
class Solution {
public:
    int getMinimumDifference(TreeNode* root) {
        int ans = INT_MAX;
        int* prev = nullptr;
        inOrder(root, ans, prev);
        
        return ans;
    }
    
private:
    // returns the max number
    void inOrder(TreeNode* cur, int& ans, int*& prev) {
        if (!cur) return;
        
        inOrder(cur->left, ans, prev);
        if (prev) ans = std::min(ans, cur->val - *prev);
        prev = &(cur->val);
        inOrder(cur->right, ans, prev);
    }
};