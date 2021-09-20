#include <utility>
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
// S: O(n)
class Solution {
public:
    TreeNode* subtreeWithAllDeepest(TreeNode* root) {
        if (!root) return root;
        
        auto pair = getDepthRoot_(root);
        return pair.second;
    }
    
private:
    std::pair<int, TreeNode*> getDepthRoot_(TreeNode* cur) {
        if (!cur) return {-1, nullptr};
        
        auto left_pair = getDepthRoot_(cur->left);
        auto right_pair = getDepthRoot_(cur->right);
        
        int depth = std::max(left_pair.first, right_pair.first) + 1;
        // if the right part has deeper depth then the answer of the left subtree is the answer of current subtree
        return left_pair.first == right_pair.first ? std::make_pair(depth, cur) :
            left_pair.first < right_pair.first ? std::make_pair(depth, right_pair.second) : std::make_pair(depth, left_pair.second);
    }
};