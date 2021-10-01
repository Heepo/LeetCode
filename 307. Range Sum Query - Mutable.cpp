#include <vector>
using namespace std;

struct SegmentTreeNode {
    // when it's a leaf, the start == end == index, sum == val
    int start;
    int end;
    int sum;
    SegmentTreeNode* left;
    SegmentTreeNode* right;
    
    SegmentTreeNode(int start, int end, int sum, SegmentTreeNode* left, SegmentTreeNode* right):
        start(start), end(end), sum(sum), left(left), right(right) {}
};

class NumArray {
public:
    NumArray(vector<int>& nums) {
        root_ = buildSegmentTree_(nums, 0, nums.size() - 1);
    }
    
    void update(int index, int val) {
        updateSegmentTree_(root_, index, val);
    }
    
    int sumRange(int left, int right) {
        return sumRange_(root_, left, right);
    }

private:
    SegmentTreeNode* root_;
    // balanced binary tree
    // T: O(n)
    // S: O(n)
    SegmentTreeNode* buildSegmentTree_(vector<int>& nums, int start, int end) {
        if (nums.empty()) return nullptr;
        // leaves
        if (start == end) return new SegmentTreeNode(start, end, nums[start], nullptr, nullptr);
        
        int mid = (start + end) / 2;
        SegmentTreeNode* left = buildSegmentTree_(nums, start, mid);
        SegmentTreeNode* right = buildSegmentTree_(nums, mid + 1, end);
        
        return new SegmentTreeNode(start, end, left->sum + right->sum, left, right);
    }
    
    // T: O(logn)
    // S: O(1)
    void updateSegmentTree_(SegmentTreeNode* cur, int index, int val) {
        int start = cur->start;
        int end = cur->end;
        if (start == end && start == index) {
            cur->sum = val;
            return;
        }
        
        int mid = (start + end) / 2;
        if (index >= start && index <= mid) updateSegmentTree_(cur->left, index, val);
        if (index >= mid + 1 && index <= end) updateSegmentTree_(cur->right, index, val);
        
        // updates val
        cur->sum = cur->left->sum + cur->right->sum;
        
        return;
    }
    
    // T: O(logn + k) where k is the reported segments number
    int sumRange_(SegmentTreeNode* cur, int left, int right) {
        if (left == cur->start && right == cur->end) return cur->sum;
        
        int mid = (cur->start + cur->end) / 2;
        if (cur->start <= left && right <= mid) return sumRange_(cur->left, left, right);
        if (mid + 1 <= left && right <= cur->end) return sumRange_(cur->right, left, right);
        
        // spans across left and right subtrees
        return sumRange_(cur->left, left, mid) + sumRange_(cur->right, mid + 1, right);
    }
};

// FenwickTree, the same as BinaryIndexedTree(BIT)
// build tree T: O(nlogn), S: O(n)
// update one element T: O(logn)
// query T: O(logn)
class FenwickTree {
public:
    FenwickTree(vector<int>& nums): partial_sums(nums.size() + 1, 0) {
        for (int i = 0; i < nums.size(); ++i) {
            int j = i + 1;
            while (j < partial_sums.size()) {
                partial_sums[j] += nums[i];
                j += lowBit(j);
            } 
        }
    }
    
    void update(int index, int val) {
        // std::cout << "update val: " << val;
        ++index;
        while (index < partial_sums.size()) {
            // std::cout << " index: " << index << std::endl;
            partial_sums[index] += val;
            index += lowBit(index);
        }
    }
    
    int query(int index) {
        ++index;
        int sum = 0;
        // std::cout << "index: " << index;
        while (index > 0) {
            sum += partial_sums[index];
            index -= lowBit(index);
        }
        // std::cout << " sum: " << sum << std::endl;
        
        return sum;
    }

private:
    vector<int> partial_sums;
    
    inline int lowBit(int x) {
        return x & (-x);
    }
};

class NumArray2 {
public:
    NumArray2(vector<int>& nums): bit_(nums), nums_(std::move(nums)) {}
    
    void update(int index, int val) {
        bit_.update(index, val - nums_[index]);
        nums_[index] = val;
    }
    
    int sumRange(int left, int right) {
        return bit_.query(right) - bit_.query(left - 1);
    }

private:
    FenwickTree bit_;
    vector<int> nums_;
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * obj->update(index,val);
 * int param_2 = obj->sumRange(left,right);
 */