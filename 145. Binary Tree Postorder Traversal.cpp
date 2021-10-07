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

// two-stacks
class Solution1 {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        if (!root) return {};
        
        s1_ = stack<TreeNode*>();
        s2_ = stack<TreeNode*>();
        
        s1_.push(root);
        while (!s1_.empty()) {
            TreeNode* curr = s1_.top();
            s1_.pop();
            
            s2_.push(curr);
            if (curr->left) s1_.push(curr->left);
            if (curr->right) s1_.push(curr->right);
        }
        
        vector<int> ans;
        while (!s2_.empty()) {
            ans.push_back(s2_.top()->val);
            s2_.pop();
        }
        
        return ans;
    }

private:
    stack<TreeNode*> s1_;
    stack<TreeNode*> s2_;
};

// one stack
// every time visits a non-null node, pushes it twice then goes to left until there isn't then starts to pop
// when popped value is the same as the top value of stack, visits the right child
// repeats until the stack is empty
class Solution2 {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        if (!root) return {};
        
        s_ = stack<TreeNode*>();
        TreeNode* curr = root;
        vector<int> ans;
        while (true) {
            while (curr) {
                s_.push(curr);
                s_.push(curr);
                curr = curr->left;
            }
            
            if (s_.empty()) return ans;
            
            curr = s_.top();
            s_.pop();
            
            // redundant root for visiting right subtree
            if (!s_.empty() && s_.top() == curr) {
                curr = curr->right;
            } else {
                // second root is for printing
                ans.push_back(curr->val);
                // or else curr will go to the above while to be pushed twice again
                curr = nullptr;
            }
        }
        return ans;
    }

private:
    stack<TreeNode*> s_;
};

// one-stack
// root->right->left order traversal, then reverse the result, elegant!
// we could uses deque to avoid the reversing operation
class Solution3 {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        if (!root) return {};

        deque<int> dq_;
        s_.push(root);
        while (!s_.empty()) {
            TreeNode* curr = s_.top();
            s_.pop();
            dq_.push_front(curr->val);
            
            if(curr->left) s_.push(curr->left);
            if(curr->right) s_.push(curr->right);
        }
        
        return vector<int>(dq_.begin(), dq_.end());
    }

private:
    stack<TreeNode*> s_;
};