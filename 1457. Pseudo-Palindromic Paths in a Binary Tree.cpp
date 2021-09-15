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
    
    // at most one number can occur odd number of times
    int pseudoPalindromicPaths (TreeNode* root) {
        if (!root) return 0;
        
        vector<int> counts(10, 0);
        return dfs(root, counts);
    }
    
    // from the root through cur, into the left subtree and the right subtree, how many paths are pseudo palindromic?
    int dfs(TreeNode* cur, vector<int>& counts) {
        if (!cur) return 0;
        
        counts[cur->val]++;
        if (!cur->left && !cur->right) {
            int odd_num = 0;
            for (int count: counts) {
                if (count % 2 == 1) odd_num++;
            }

            // back tracking
            counts[cur->val]--;
            if (odd_num <= 1) return 1;
            return 0;
        }
        
        int left_paths = dfs(cur->left, counts);
        int right_paths = dfs(cur->right, counts);
        // back tracking
        counts[cur->val]--;
        
        return left_paths + right_paths;
    }
};

class Solution2 {
public:
    
    // at most one number can occur odd number of times
    // uses binary status to record the odd / even times appeared at the corresponding postions
    int pseudoPalindromicPaths (TreeNode* root) {
        if (!root) return 0;
        
        return dfs(root, 0);
    }
    
    int dfs(TreeNode* cur, int status) {
        if (!cur) return 0;
        status ^= (1 << cur->val);
        int ans = 0;
        if (!cur->left && !cur->right)
            // one-bits means the position number appeared odd times
            ans += __builtin_popcount(status) <= 1;
        ans += dfs(cur->left, status);
        ans += dfs(cur->right, status);
        
        return ans;
    }
};