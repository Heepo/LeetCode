#include <vector>
#include <unordered_map>
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

// when one of the traversal is in-order the construction result is the one and the only
// uses a hashmap to record the positions of post-order traversal
// T: O(n)
// S: O(logn) ~ O(n)
class Solution {
public:
    TreeNode* constructFromPrePost(vector<int>& preorder, vector<int>& postorder) {
        if (preorder.empty() || preorder.size() != postorder.size()) return nullptr;
        
        unordered_map<int, int> post_map;
        for (int i = 0; i < postorder.size(); ++i) {
            post_map[postorder[i]] = i;
        }
        
        return construct_(preorder, post_map, 0, 0, postorder.size() - 1);
    }
    
private:
    TreeNode* construct_(vector<int>& preorder, unordered_map<int, int>& post_map,
                         int pre_start, int post_start, int post_end) {
        if (post_start > post_end) return nullptr;
        TreeNode* root = new TreeNode(preorder[pre_start]);
        if (post_start == post_end) return root;
        
        int cut = post_map[preorder[pre_start + 1]];
        root->left = construct_(preorder, post_map, pre_start + 1, post_start, cut);
        root->right = construct_(preorder, post_map, pre_start + cut - post_start + 2, cut + 1, post_end - 1);
        
        return root;
    }
};