#include <algorithm>
#include <map>
#include <memory>
using namespace std;

// uses ordered map to store the event times happening right on that point (start times - end times)
// scans the map to get the max accumulated event times, i.e. the max overlapping events
// T:O(n^2), n is the number of booking times. The i-th booking will take O(logn) to insert it to the map, and O(i) to scan the map.
// S:O(n)
class MyCalendarThree {
public:
    MyCalendarThree() {}
    
    int book(int start, int end) {
        index_count_[start]++;
        index_count_[end]--;
        
        int ans = 0;
        int accum = 0;
        for (auto e: index_count_) {
            accum += e.second;
            ans = max(ans, accum);
        }
        
        return ans;
    }
    
private:
    map<int, int> index_count_;
    
};

class SegmentTree {
public:
    SegmentTree():root_(new TreeNode()), max_count_(0) {}
    
    int update(int start, int end) {
        update_(root_, start, end);
        return max_count_;
    }

private:
    struct TreeNode {
        int start;
        int mid; // split the range to two parts [start, mid) and [mid, end)
        int end;
        int count; // the count of full coverage on [start, end)
        unique_ptr<TreeNode> left; // dynamicly creates nodes using smart pointer to avoid memory leak
        unique_ptr<TreeNode> right;
        
        TreeNode():start(INT_MIN), mid(-1), end(INT_MAX), count(0), left(nullptr), right(nullptr) {};
        TreeNode(int start, int end, int count):start(start), mid(-1), end(end), count(count), left(nullptr), right(nullptr) {};
    };
    
    TreeNode* root_;
    int max_count_;
    
    // T: O(nlogn) ~ O(n^2), each update needs to recursively build the tree
    // S: O(n)
    void update_(TreeNode* cur, int start, int end) {
        // current node has been splitted
        if (cur->mid != -1) {
            if (end <= cur->mid) update_(cur->left.get(), start, end);
            else if (start >= cur->mid) update_(cur->right.get(), start, end);
            else {
                if (cur->start == start && cur->end == end) max_count_ = max(max_count_, ++cur->count);
                update_(cur->left.get(), start, cur->mid);
                update_(cur->right.get(), cur->mid, end);
            }
            
            return;
        }
        
        if (cur->start == start && cur->end == end) {
            max_count_ = max(max_count_, ++cur->count);
            return;
        }
        
        // prefers to use start to split the range
        if (start > cur->start) {
            cur->mid = start;
            cur->left.reset(new TreeNode(cur->start, start, cur->count));
            cur->right.reset(new TreeNode(start, cur->end, cur->count));
            update_(cur->right.get(), start, end);
            return;
        }
        
        // end < cur->end && start == cur->start
        cur->mid = end;
        cur->left.reset(new TreeNode(cur->start, end, cur->count));
        cur->right.reset(new TreeNode(end, cur->end, cur->count));
        update_(cur->left.get(), start, end);
        
        return;
    }
};

// uses a segment tree to store the range and the count in that range
// each updates will update the max count of the tree also
// T: O(nlogn) ~ O(n^2), each update needs to recursively build the tree
// S: O(n)
class MyCalendarThree2 {
public:
    MyCalendarThree2():tree_(new SegmentTree()) {}
    
    int book(int start, int end) {  
        return tree_->update(start, end);
    }
    
private:
    SegmentTree* tree_;
    
};

/**
 * Your MyCalendarThree object will be instantiated and called as such:
 * MyCalendarThree* obj = new MyCalendarThree();
 * int param_1 = obj->book(start,end);
 */