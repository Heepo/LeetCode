#include <vector>
#include <stack>
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
    vector<double> averageOfLevels(TreeNode* root) {
        if (!root) return {};
        
        vector<std::pair<long long, int>> sum_count;
        vector<double> ans;
        
        dfs_(root, 0, sum_count);
        
        for (const auto& p: sum_count) {
            ans.push_back(static_cast<double>(p.first) / p.second);
        }
        
        return ans;
    }
    
private:
    void dfs_(TreeNode* curr, int depth, vector<std::pair<long long, int>>& sum_count) {
        if (!curr) return;
        
        if (depth == sum_count.size()) sum_count.push_back({0, 0});
        sum_count[depth].first += curr->val;
        sum_count[depth].second++;

        dfs_(curr->left, depth + 1, sum_count);
        dfs_(curr->right, depth + 1, sum_count);
        return;
    }
};

class Solution2 {
public:
    vector<double> averageOfLevels(TreeNode* root) {
        if (!root) return {};
        
        vector<double> ans;
        bfs_(root, ans);
        
        return ans;
    }
    
private:
    void bfs_(TreeNode* curr, vector<double>& ans) {
        stack<TreeNode*> s1;
        s1.push(curr);
        
        stack<TreeNode*> s2;
        while (!s1.empty()) {
            double sum = 0;
            int count = 0;
            while (!s1.empty()) {
                TreeNode* node = s1.top();
                s1.pop();
                sum += node->val;
                count++;
                
                if (node->left) s2.push(node->left);
                if (node->right) s2.push(node->right);
            }
            
            ans.push_back(sum / count);
            s1.swap(s2);
        }

        return;
        
    }
};