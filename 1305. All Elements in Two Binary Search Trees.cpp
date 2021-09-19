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

// inorder traverses both trees then merge the two arrays
// T: O(n+m)
// S: O(n+m)
class Solution1 {
public:
    vector<int> getAllElements(TreeNode* root1, TreeNode* root2) {
        if (!root1 && !root2) return {};
        
        vector<int> array1, array2;
        inOrder(root1, array1);
        inOrder(root2, array2);
        return merge(array1, array2);
    }
    
    void inOrder(TreeNode* cur, vector<int>& array) {
        if (!cur) return;
        
        inOrder(cur->left, array);
        array.push_back(cur->val);
        inOrder(cur->right, array);
        return;
    }
    
    vector<int> merge(vector<int>& array1, vector<int>& array2) {
        int i = 0;
        int j = 0;
        vector<int> merged;
        while (i < array1.size() || j < array2.size()) {
            if (i < array1.size() && j < array2.size()) {
                if (array1[i] < array2[j]) {
                    merged.push_back(array1[i]);
                    i++;
                } else {
                    merged.push_back(array2[j]);
                    j++;
                }
                continue;
            }
            
            if (i < array1.size()) {
                merged.push_back(array1[i]);
                i++;
            }
            
            if (j < array2.size()) {
                merged.push_back(array2[j]);
                j++;
            }
        }
        
        return merged;
    }
    
};

// inorder traverses both trees only once, merging values during the traversal using stacks
// T: O(n+m)
// S: O(n+m)
class Solution2 {
public:
    vector<int> getAllElements(TreeNode* root1, TreeNode* root2) {
        if (!root1 && !root2) return {};
        
        vector<int> ans;
        inOrder(root1, root2, ans);
        
        return ans;
    }
    
    // firstly dives into the most left node and pushes all the nodes in the path
    // then pop a element once at a time, then visits its right child, and repeats the above operations.
    // the popout elements will be in the right order
    void inOrder(TreeNode* cur1, TreeNode* cur2, vector<int>& ans) {
        stack<TreeNode*> s1_;
        stack<TreeNode*> s2_;
        leftMost(cur1, s1_);
        leftMost(cur2, s2_);
        
        while (!s1_.empty() || !s2_.empty()) {
            TreeNode* top_;
            if (s1_.empty()) {
                top_ = s2_.top();
                s2_.pop();
                ans.push_back(top_->val);
                leftMost(top_->right, s2_);
            } else if (s2_.empty()) {
                top_ = s1_.top();
                s1_.pop();
                ans.push_back(top_->val);
                leftMost(top_->right, s1_);
            } else {
                if (s1_.top()->val < s2_.top()->val) {
                    top_ = s1_.top();
                    s1_.pop();
                    ans.push_back(top_->val);
                    leftMost(top_->right, s1_);
                } else {
                    top_ = s2_.top();
                    s2_.pop();
                    ans.push_back(top_->val);
                    leftMost(top_->right, s2_);
                }
            }
        }
        
        return;
    }
    
    void leftMost(TreeNode* cur, stack<TreeNode*>& s) {
        if (!cur) return;
        
        s.push(cur);
        leftMost(cur->left, s);
        
        return;
    }
};