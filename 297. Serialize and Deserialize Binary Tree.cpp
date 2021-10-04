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

// uses pre-order traversal to serialize/deserialize the tree
// appends val to string will cost O(length).
// T: O(n^2)
// S: O(n)
class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        if (!root) return "";
        
        string ans = "";
        serialize_(root, ans);
        // std::cout << "serialized: " << ans << std::endl;
        return ans;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        if (data == "") return nullptr;

        int s = 0;
        return deserialize_(data, s);
        
    }
    
private:
    void serialize_(TreeNode* cur, string& ans) {
        if (!cur) {
            ans += "# ";
            return;
        }
        
        ans += std::to_string(cur->val) + " ";
        serialize_(cur->left, ans);
        serialize_(cur->right, ans);
    }
    
    TreeNode* deserialize_(string& data, int& index) {
        int length = 0;
        for (; index < data.size(); ++index) {
            if (data[index] == ' ') {
                ++index;
                break;
            }
            
            length++;
        }
        
        if (length == 1 && data[index - length - 1] == '#') return nullptr;
        
        TreeNode* cur = new TreeNode(std::stoi(data.substr(index - length - 1, length)));
        cur->left = deserialize_(data, index);
        cur->right = deserialize_(data, index);
        return cur;
    }
};

// uses pre-order traversal to serialize/deserialize the tree
// just copy the memory bytes representing the node values to the stream, no string conversion needed
// Creates a flag to represent its status, so one node will only cost 5 bytes
// T: O(n)
// S: O(n)
class Codec2 {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        if (!root) return "";
        
        ostringstream out;
        serialize_(root, out);
        // std::cout << "serialized: " << ans << std::endl;
        return out.str();
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        if (data == "") return nullptr;

        istringstream in(data);
        return deserialize_(in);
    }
    
private:
    enum STATUS {
        ROOT_NULL = 0x00,
        ROOT = 0x01,
        LEFT = 0x02,
        RIGHT = 0x04,
    };
    
    void serialize_(TreeNode* cur, ostringstream& out) {
        char status = 0;
        if (cur) {
            status |= ROOT;
            if (cur->left) status |= LEFT;
            if (cur->right) status |= RIGHT;
        }
        out.write(&status, sizeof(status));
        
        if (!cur) return;
        out.write(reinterpret_cast<char*>(&(cur->val)), sizeof(cur->val));
        
        if (status & LEFT) serialize_(cur->left, out);
        if (status & RIGHT) serialize_(cur->right, out);
    }
    
    TreeNode* deserialize_(istringstream& in) {
        char status;
        in.read(&status, sizeof(status));
        if (!status) return nullptr;

        TreeNode* root = new TreeNode();
        in.read(reinterpret_cast<char*>(&(root->val)), sizeof(root->val));
        
        root->left = (status & LEFT) ? deserialize_(in) : nullptr;
        root->right = (status & RIGHT) ? deserialize_(in) : nullptr;
        return root;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));