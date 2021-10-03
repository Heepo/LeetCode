#include <algorithm>
#include <vector>
#include <memory>
using namespace std;

class SegmentTree {
public:
    SegmentTree():root_(new TreeNode()), max_height(0), affected_max_height(0), join_() {}
    
    int update(int start, int end) {
        join_.clear();
        affected_max_height = 0;

        update_(root_, start, end, end - start);
        for (TreeNode* node: join_) node->height = affected_max_height;

        return max_height;
    }

private:
    struct TreeNode {
        int start;
        int mid; // split the range to two parts [start, mid) and [mid, end)
        int end;
        int height; // the height of full coverage on [start, end)
        unique_ptr<TreeNode> left; // dynamicly creates nodes using smart pointer to avoid memory leak
        unique_ptr<TreeNode> right;
        
        TreeNode():start(INT_MIN), mid(-1), end(INT_MAX), height(0), left(nullptr), right(nullptr) {};
        TreeNode(int start, int end, int height):start(start), mid(-1), end(end), height(height), left(nullptr), right(nullptr) {};
    };
    
    TreeNode* root_;
    int max_height;
    vector<TreeNode*> join_;
    int affected_max_height;
    
    // T: O(nlogn) ~ O(n^2), each update needs to recursively build the tree
    // S: O(n)
    void update_(TreeNode* cur, int start, int end, int height) {
        // current node has been splitted
        if (cur->mid != -1) {
            if (end <= cur->mid) update_(cur->left.get(), start, end, height);
            else if (start >= cur->mid) update_(cur->right.get(), start, end, height);
            else {
                if (cur->start == start && cur->end == end) {
                    max_height = max(max_height, cur->height += height);
                    affected_max_height = max(affected_max_height, cur->height);
                    join_.push_back(cur);
                }
                update_(cur->left.get(), start, cur->mid, height);
                update_(cur->right.get(), cur->mid, end, height);
            }
            
            return;
        }
        
        if (cur->start == start && cur->end == end) {
            max_height = max(max_height, cur->height += height);
            affected_max_height = max(affected_max_height, cur->height);
            join_.push_back(cur);

            return;
        }
        
        // prefers to use start to split the range
        if (start > cur->start) {
            cur->mid = start;
            cur->left.reset(new TreeNode(cur->start, start, cur->height));
            cur->right.reset(new TreeNode(start, cur->end, cur->height));
            update_(cur->right.get(), start, end, height);
            
            return;
        }
        
        // end < cur->end && start == cur->start
        cur->mid = end;
        cur->left.reset(new TreeNode(cur->start, end, cur->height));
        cur->right.reset(new TreeNode(end, cur->end, cur->height));
        update_(cur->left.get(), start, end, height);
        
        return;
    }
};

// uses a vector to store the affected nodes, and updates all of them by their max height
// T: O(nlogn) ~ O(n^2)
// S: O(n)
class Solution {
public:
    vector<int> fallingSquares(vector<vector<int>>& positions) {
        vector<int> ans;
        
        SegmentTree tree_;
        for (auto position: positions) ans.push_back(tree_.update(position[0], position[1] + position[0]));
        
        return ans;
    }
};