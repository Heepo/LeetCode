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
    int findSecondMinimumValue(TreeNode* root) {
        if (!root) return -1;
        
        int m1 = root->val;
        int m2 = -1;
        
        // dfs_(root, m1, m2);
        bfs_(root, m1, m2);
        
        return m2;
    }
    
private:
    void dfs_(TreeNode* curr, const int& m1, int& m2) {
        if (!curr) return;
        
        if (curr->val != m1) {
            if (m2 == -1) m2 = curr->val;
            else m2 = min(m2, curr->val);
            return;
        }
        
        dfs_(curr->left, m1, m2);
        dfs_(curr->right, m1, m2);
    }
    
    void bfs_(TreeNode* curr, const int& m1, int& m2) {
        queue<TreeNode*> q;
        q.push(curr);
        
        while(!q.empty()) {
            TreeNode* curr = q.front();
            q.pop();
            
            if (curr->val != m1) {
                if (m2 == -1) m2 = curr->val;
                else m2 = min(m2, curr->val);
                
                continue;
            }
            if(curr->left) q.push(curr->left);
            if(curr->right) q.push(curr->right);
        }
    }
};