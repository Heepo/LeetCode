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

// T: O(n) for traversal
// S: O(n) for saving the sorted array
class Solution {
public:
    TreeNode* balanceBST(TreeNode* root) {
        // gets the sorted value array by inorder traversal
        // then builds the balanced search tree from the array recursively
        if (!root) return root;
        
        vector<TreeNode*> array;
        inOrder(array, root);
        return buildFromArray(array, 0, array.size() - 1);
    }
    
    void inOrder(vector<TreeNode*>& array, TreeNode* cur) {
        if (!cur) return;
        inOrder(array, cur->left);
        array.push_back(cur);
        inOrder(array, cur->right);
        return;
    }
    
    TreeNode* buildFromArray(vector<TreeNode*>& array, int start, int end) {
        if (start > end) return (TreeNode*)nullptr;
        int mid = (start + end) / 2;
        // if mid == start == end, then both children will be nullptr
        array[mid]->left = buildFromArray(array, start, mid - 1);
        array[mid]->right = buildFromArray(array, mid + 1, end);
        return array[mid];
    };
};