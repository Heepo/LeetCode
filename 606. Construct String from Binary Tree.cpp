#include <string>
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
    string tree2str(TreeNode* root) {
        if (!root) return "";
        
        const string self = std::to_string(root->val);
        const string l = tree2str(root->left);
        const string r = tree2str(root->right);
        
        if (l == "" && r == "") return self;
        if (r == "") return self + "(" + l + ")";
        return self + "(" + l + ")" + "(" + r + ")";
    }
};