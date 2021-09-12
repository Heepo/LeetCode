#include <vector>
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
    int widthOfBinaryTree(TreeNode* root) {
        // re-id the nodes from the leftmost non-null node to the leftmost non-null node
        // the id start from 0, then the left child's id will be 2 * i + 1, the right child's id will be 2 * i + 2
        // at last substract the left most non-null node's id
        if (!root) return 0;
        vector<long> level_start_ids;
        
        return dfs(root, level_start_ids, 0, 1);
    }
    
    // returns the max width when the subtree with cur as its root is the right most
    long dfs(TreeNode* cur, vector<long>& level_start_ids, long id, int level) {
        if (!cur) return 0;
        if (level_start_ids.size() < level) level_start_ids.push_back(id);

        //std::cout << "id: " << id << " level_start_ids[level - 1]: " << level_start_ids[level - 1]
        //    << " re-id: " << id - level_start_ids[level - 1] << std::endl;
        return max(id - level_start_ids[level - 1] + 1, max(
            dfs(cur->left, level_start_ids, 2 * (id - level_start_ids[level - 1]) + 1, level + 1),
            dfs(cur->right, level_start_ids, 2 * (id - level_start_ids[level - 1]) + 2, level + 1)));
    }
};