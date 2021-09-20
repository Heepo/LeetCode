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

// T: O(n) for post-order traversal
// S: O(n) in worst case using stack
class Solution {
public:
    int distributeCoins(TreeNode* root) {
        if (!root) return 0;
        
        int ans = 0;
        balance(root, ans);
        return ans;
    }
    
    int balance(TreeNode* cur, int& ans) {
        if (!cur) return 0;
        
        // calculates the redundant coins number, which needs to flow through the link
        // the number can be positive(flows up) or negative(flows down)
        int left_extra = balance(cur->left, ans);
        int right_extra = balance(cur->right, ans);
        ans += abs(left_extra) + abs(right_extra);
        
        // if extra is positive then extra coins will need to flow to its parent subtree
        // else flow down extra coins
        int extra = left_extra + right_extra + cur->val - 1;
        
        return extra;
    }
};