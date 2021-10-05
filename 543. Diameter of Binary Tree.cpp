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

// T: O(n)
// S: O(h)
class Solution {
public:
    int diameterOfBinaryTree(TreeNode* root) {
        if (!root) return 0;
        
        int ans = 0;
        pathSum_(root, ans);
        
        return ans;
    }
    
private:
    // returns the max path length of one subtree
    int pathSum_(TreeNode* curr, int& ans) {
        if (!curr) return -1;
        
        int l = pathSum_(curr->left, ans);
        int r = pathSum_(curr->right, ans);
        ans = max(ans, l + r + 2);
        
        return max(l + 1, r + 1);
    }
};