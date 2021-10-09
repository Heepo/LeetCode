#include <vector>
#include <string>
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
    vector<vector<string>> printTree(TreeNode* root) {
        if (!root) return {};
        
        int h = height_(root);
        int column_num = (1 << h) - 1;
        
        vector<vector<string>> ans = vector<vector<string>>(h, vector<string>(column_num, ""));
        fill_(root, ans, 0, 0, column_num - 1);
        return ans;
    }
    
private:
    int height_(TreeNode* curr) {
        if (!curr) return 0;
        
        return max(height_(curr->left), height_(curr->right)) + 1;
    }
    
    void fill_(TreeNode* curr, vector<vector<string>>& ans, int height, int start, int end) {
        if (!curr) return;
        
        int mid = (start + end) / 2;
        ans[height][mid] = std::to_string(curr->val);
        fill_(curr->left, ans, height + 1, start, mid - 1);
        fill_(curr->right, ans, height + 1, mid + 1, end);
        return;
    }
};