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
    vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
        if (!root) return {};
        target_ = targetSum;
        
        vector<int> path;
        vector<vector<int>> ans;
        int sum = 0;
        pathSum_(root, path, ans, sum);
        return ans;
    }

private:
    int target_;
    
    void pathSum_(TreeNode* curr, vector<int>& path, vector<vector<int>>& ans, int& sum) {
        if (!curr) return;
        
        path.push_back(curr->val);
        sum += curr->val;
        if (!curr->left && !curr->right && sum == target_)
            ans.push_back(path);
        else {
            pathSum_(curr->left, path, ans, sum);
            pathSum_(curr->right, path, ans, sum);
        }
        // DO NOT forget to pop back
        path.pop_back();
        sum -= curr->val;
    }
};