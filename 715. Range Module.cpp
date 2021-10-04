#include <algorithm>
#include <map>
using namespace std;

// uses a map(AVL/BST) to store the ranges with left range as the key
// add/remove needs to merge/delete all the overlapped ranges(number m).
// add/remove T: O(mlogn)
// Query T: O(logn)
class RangeModule {
public:
    RangeModule():ranges_() {}
    
    void addRange(int left, int right) {
        map<int, int>::iterator first = ranges_.end();
        map<int, int>::iterator last = ranges_.end();
        // T: O(logn)
        getOverlappedRanges(left, right, first, last);
        
        // exists overlapped ranges
        if (first != last) {
            left = min(left, first->first);
            right = max(right, (--last)->second);
            // erases overlapped ranges. T: O(mlogn) because each deletion(/insertion/search) in AVL cost O(logn)
            ranges_.erase(first, ++last);
        }
        
        ranges_[left] = right;
    }
    
    bool queryRange(int left, int right) {
        map<int, int>::iterator first = ranges_.end();
        map<int, int>::iterator last = ranges_.end();
        // T: O(logn)
        getOverlappedRanges(left, right, first, last);
        
        if (first == last) return false;
        // only true when all covered in the first range
        return left >= first->first && right <= first->second;
    }
    
    void removeRange(int left, int right) {
        map<int, int>::iterator first = ranges_.end();
        map<int, int>::iterator last = ranges_.end();
        // T: O(logn)
        getOverlappedRanges(left, right, first, last);
        
        if (first == last) return;
        
        auto l_it = last;
        int f = first->first;
        int l = (--last)->second;
        // T: O(mlogn)
        ranges_.erase(first, l_it);
        
        if (left > f) ranges_[f] = left;
        if (right < l) ranges_[right] = l;

        return;
    }
    
private:
    map<int, int> ranges_;
    
    // [first, last) is half-open
    void getOverlappedRanges(int left, int right, map<int, int>::iterator& first, map<int, int>::iterator& last) {
        // upper_bound > right, lower_bound >= right
        // T: O(logn)
        last = ranges_.upper_bound(right);
        first = ranges_.upper_bound(left);
        if (first != ranges_.begin() && (--first)->second < left) ++first;
        
        return;
    }
    
};

/**
 * Your RangeModule object will be instantiated and called as such:
 * RangeModule* obj = new RangeModule();
 * obj->addRange(left,right);
 * bool param_2 = obj->queryRange(left,right);
 * obj->removeRange(left,right);
 */