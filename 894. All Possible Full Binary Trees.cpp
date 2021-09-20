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
    vector<TreeNode*> allPossibleFBT(int n) {
        if (n % 2 == 0) return {};
        
        // actually n must be odd
        vector<vector<TreeNode*>> dp = vector<vector<TreeNode*>>(n + 1, vector<TreeNode*>{});
        // initializes the dp vector
        dp[1].push_back(new TreeNode());
        
        for (int total = 3; total <= n; total += 2) {
            for (int left_total = 1; left_total <= total - 2; left_total += 2) {
                int right_total = total - left_total - 1;
                for (auto l: dp[left_total]) {
                    for (auto r: dp[right_total]) {
                        TreeNode* root = new TreeNode(0);
                        root->left = l;
                        root->right = r;
                        dp[total].push_back(root);
                    }
                }
                
            }
        }
        
        return dp[n];
    }
};