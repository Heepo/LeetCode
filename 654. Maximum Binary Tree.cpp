#include <algorithm>
#include <vector>
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
    TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
        if (nums.empty()) return nullptr;
        
        return dfs_(nums, 0, nums.size());
    }
    
private:
    TreeNode* dfs_(vector<int>& nums, int start, int end) {
        if (start == end) return nullptr;
        
        auto it = std::max_element(nums.begin() + start, nums.begin() + end);
        TreeNode* curr = new TreeNode(*it);
        int index = it - nums.begin();
        curr->left = dfs_(nums, start, index);
        curr->right = dfs_(nums, index + 1, end);
        
        return curr;
    }
};