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
    // players can only choose uncolored neighbours of previous named node
    // once the other player choose one of the neighbours, then other nodes connected to that neighbour are cutted off and can't be visited by the player
    bool btreeGameWinningMove(TreeNode* root, int n, int x) {
        if (!root || n == 1) return false;
        
        count_(root, x);
        int parent_sub_count = n - (left_sub_count + right_sub_count + 1);        
        return max(parent_sub_count, max(left_sub_count, right_sub_count)) > n / 2;
    }

private:
    int left_sub_count;
    int right_sub_count;
    
    int count_(TreeNode* cur, int x) {
        if (!cur) return 0;
        
        int left_count = count_(cur->left, x);
        int right_count = count_(cur->right, x);
        
        if(cur->val == x) {
            left_sub_count = left_count;
            right_sub_count = right_count;
        }
        
        return left_count + right_count + 1;
    }
};