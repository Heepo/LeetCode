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