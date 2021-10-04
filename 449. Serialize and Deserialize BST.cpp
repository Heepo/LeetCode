#include <string>
#include <sstream>
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

// Copies memory bytes of node values to string stream instead of string converting will save a lot of time
// Also, BST has a good feature that only using the preorder traversal can recover the tree because the inorder traversal is ordered
// T: O(n)
// S: O(n)
class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        if (!root) return "";
        
        ostringstream out;
        serialize_(root, out);
        return out.str();
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        if (data == "") return nullptr;
        
        istringstream in(data);
        // subtree range
        int l = INT_MIN;
        int r = INT_MAX;
        TreeNode* unallocated = nullptr;
        return deserialize_(in, l, r, unallocated);
    }
    
private:
    void serialize_(TreeNode* cur, ostringstream& out) {
        if (!cur) return;
        
        out.write(reinterpret_cast<char*>(&(cur->val)), sizeof(cur->val));
        serialize_(cur->left, out);
        serialize_(cur->right, out);
    }
    
    TreeNode* deserialize_(istringstream& in, int l, int r, TreeNode*& unallocated) {
        // all allocated, continues to read
        if (!unallocated) {
            // end of stream
            if (in.peek() == EOF) return nullptr;
            
            TreeNode* root = new TreeNode();
            in.read(reinterpret_cast<char*>(&(root->val)), sizeof(root->val));
            unallocated = root;
        }
        
        // std::cout << "l: " << l << " r: " << r << " unallocated->val: " << unallocated->val << std::endl;
        // belongs to this subtree
        if (unallocated->val > l && unallocated->val < r) {
            TreeNode* root = unallocated;
            unallocated = nullptr;
            root->left = deserialize_(in, l, root->val, unallocated);
            root->right = deserialize_(in, root->val, r, unallocated);
            return root;
        }
        
        // beyond this subtree
        return nullptr;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec* ser = new Codec();
// Codec* deser = new Codec();
// string tree = ser->serialize(root);
// TreeNode* ans = deser->deserialize(tree);
// return ans;