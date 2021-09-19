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

// T: O(n) for traversal
// S: O(logn) -> O(n)
class Solution {
public:
    int maxProduct(TreeNode* root) {
        if (!root) return 0;
        
        // calculates the total sum of the tree
        long total = sum(root);
        
        long ans = 0;
        max_product(ans, total, root);
        
        return ans % int(1e9 + 7);
    }
    
    int sum(TreeNode* cur) {
        if (!cur) return 0;
        
        return cur->val + sum(cur->left) + sum(cur->right);
    }
    
    // for a node, there are two cutting choices: cutting the left or the right subtree.
    // updates the max product
    long max_product(long& ans, int total, TreeNode* cur) {
        if (!cur) return 0;
        
        long left_sum = max_product(ans, total, cur->left);
        long right_sum = max_product(ans, total, cur->right);
        ans = max(ans, max(left_sum * (total - left_sum), right_sum * (total - right_sum)));
        
        return left_sum + right_sum + cur->val;
    }
};