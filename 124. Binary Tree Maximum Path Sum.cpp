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
// noted that, if both subtrees are selected in the path, then the subtrees can't include both their subtrees
// recursively return the max(root, root+left_subtree, root+right_subtree) and keeps track of current max sum,
// including the possible situation root + left_subtree + right_subtree
// T: O(n)
// S: O(h)
class Solution {
public:
    int maxPathSum(TreeNode* root) {
        int ans = INT_MIN;
        
        maxOnePathSum_(root, ans);
        return ans;
    }
    
private:
    int maxOnePathSum_(TreeNode* cur, int& ans) {
        if (!cur) return 0;
        
        int max_ = cur->val;
        int left_max = maxOnePathSum_(cur->left, ans);
        int right_max = maxOnePathSum_(cur->right, ans);
        
        max_ = max(max_, cur->val + left_max);
        max_ = max(max_, cur->val + right_max);
        ans = max(ans, max(max_, cur->val + left_max + right_max));
        
        return max_;
    }
};