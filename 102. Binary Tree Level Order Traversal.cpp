#include <algorithm>
#include <queue>
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
    vector<vector<int>> levelOrder(TreeNode* root) {
        if (!root) return {};
        
        vector<vector<int>> ans;
        // dfs_(root, 0, ans);
        bfs_(root, ans);
        
        return ans;
    }
    
private:
    void dfs_(TreeNode* curr, int depth, vector<vector<int>>& ans) {
        if (!curr) return;
        
        // works with pre/in/post-order traversal
        while (ans.size() <= depth) ans.push_back({});
        
        dfs_(curr->left, depth + 1, ans);
        dfs_(curr->right, depth + 1, ans);
        ans[depth].push_back(curr->val);
    }
    
    void bfs_(TreeNode* curr, vector<vector<int>>& ans) {
        queue<TreeNode*> q1;
        q1.push(curr);
        
        queue<TreeNode*> q2;
        
        while (!q1.empty()) {
            vector<int> v;
            // one layer
            while (!q1.empty()) {
                TreeNode* curr = q1.front();
                q1.pop();
                v.push_back(curr->val);
                if (curr->left) q2.push(curr->left);
                if (curr->right) q2.push(curr->right);
            }
            ans.push_back(v);
            q1.swap(q2);
        }
    }
};