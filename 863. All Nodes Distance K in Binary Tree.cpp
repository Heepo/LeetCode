#include <vector>
#include <queue>
#include <unordered_set>
#include <unordered_map>
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

// builds an undirected graph and does BFS to collect distance-k nodes
// T: O(n)
// S: O(n)
class Solution1 {
public:
    vector<int> distanceK(TreeNode* root, TreeNode* target, int k) {
        if (!root || k < 0) return {};
        
        // O(n)
        unordered_map<TreeNode*, vector<TreeNode*>> g_;
        dfs_(root, g_);
        
        return collect_(target, g_, k);
    }
    
private:
    void dfs_(TreeNode* cur, unordered_map<TreeNode*, vector<TreeNode*>>& g) {
        if (!cur) return;
        
        if (cur->left) {
            g[cur].push_back(cur->left);
            g[cur->left].push_back(cur);
            dfs_(cur->left, g);
        }
        
        if (cur->right) {
            g[cur].push_back(cur->right);
            g[cur->right].push_back(cur);
            dfs_(cur->right, g);
        }
        return;
    }
    
    vector<int> collect_(TreeNode* cur, unordered_map<TreeNode*, vector<TreeNode*>>& g, int k) {
        vector<int> ans;
        unordered_set<TreeNode*> visited;
        queue<TreeNode*> q;
        q.push(cur);
        
        // BFS, O(n)
        while (!q.empty() && k > 0) {
            int same_distance_count = q.size();
            while (same_distance_count--) {
                TreeNode* node = q.front();
                q.pop();
                visited.insert(node);
                for (auto neighbour: g[node]) {
                    if (!visited.count(neighbour)) {
                        visited.insert(neighbour);
                        q.push(neighbour);
                    }
                }
            }
            k--;
        }
        
        while (!q.empty()) {
            TreeNode* node = q.front();
            q.pop();
            ans.push_back(node->val);
        }
        
        return ans;
    }
};

// uses DFS and calculates distance downward
// target must lie in one of the subtrees. Assumes it appears in the left subtree of root, then satisfied nodes might have three kinds of positions
// to exist. One kind is in the subtree of target, collect the nodes using dfs or bfs. Second kind is above the target but still in the left
// subtree of root, collect it when returned downward distance to target mateches k. The last kind is in the right subtree of root, let the downward
// distance from left child to target be l, then collect nodes that the downward distance from root to right subtree equals with k - l - 1
// T: O(n)
// S: O(n)
class Solution2 {
public:
    vector<int> distanceK(TreeNode* root, TreeNode* target, int k) {
        if (!root || k < 0) return {};
        
        vector<int> ans;
        distance_(root, target, k, ans);
        return ans;
    }
    
private:
    // traversal stops when cur meets target
    // returns -1 when target is not in the subtree
    int distance_(TreeNode* cur, TreeNode* target, int k, vector<int>& ans) {
        if (!cur) return -1;
        
        if (cur == target) {
            collect_(target, k, ans);
            return 0;
        }
        
        int left_child_distance = distance_(cur->left, target, k, ans);
        int right_child_distance = distance_(cur->right, target, k, ans);
        // target in left subtree
        if (left_child_distance >= 0) {
            if (left_child_distance == k - 1) ans.push_back(cur->val);
            collect_(cur->right, k - 2 - left_child_distance, ans);
            return left_child_distance + 1;
        }
        // or target in right subtree
        if (right_child_distance >= 0) {
            if (right_child_distance == k - 1) ans.push_back(cur->val);
            collect_(cur->left, k - 2 - right_child_distance, ans);
            return right_child_distance + 1;
        }
        
        return -1;
    }
    
    void collect_(TreeNode* cur, int distance, vector<int>& ans) {
        if (distance < 0 || !cur) return;
        
        if (distance == 0) {
            ans.push_back(cur->val);
            return;
        }
        
        collect_(cur->left, distance - 1, ans);
        collect_(cur->right, distance - 1, ans);
    }
};