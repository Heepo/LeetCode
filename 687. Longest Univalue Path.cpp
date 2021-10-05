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
    int longestUnivaluePath(TreeNode* root) {
        if (!root) return 0;
        
        int ans = 0;
        univaluePath_(root, ans);
        return ans;
    }
    
private:
    // returns the length, and the path MUST go THROUGH the current node
    int univaluePath_(TreeNode* curr, int& ans) {
        if(!curr) return 0;
        
        int l = univaluePath_(curr->left, ans);
        int r = univaluePath_(curr->right, ans);
        
        if (curr->left && curr->left->val == curr->val) l++;
        else l = 0;
        
        if (curr->right && curr->right->val == curr->val)
            r++;
        else r = 0;
        
        ans = max(ans, l + r);
        
        return max(l, r);
    }
};