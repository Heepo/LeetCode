#include <queue>
#include <set>
using namespace std;

// uses a max heap and a min heap(priority queues) to store half nums, the smaller half and the larger half
// keeps track of the max number and the min number of the heaps
// each time adds a new number to one of the heaps to make sure it's smaller than the max number or larger than the min number
// if the two heaps number diff > 1, balances them to ensure the diff <=1(pops max/min and transfer to the other heap)
// roots of both heaps are candidates
// T(add): heapify up O(logn), T(remove max/min for max/min heap): heapify down O(logn), T(get max/min for max/min heap): O(1)
// T: O(nlogn)
// S: O(n)
class MedianFinder {
public:
    MedianFinder() {
        
    }
    
    void addNum(int num) {
        if (max_q_.empty()) {
            max_q_.push(num);
            return;
        }
        
        if (num > max_q_.top()) min_q_.push(num);
        else max_q_.push(num);
        
        // sees if it needs to balance
        if (abs((int)max_q_.size() - (int)min_q_.size()) <= 1) return;
        
        while (max_q_.size() - 1 > min_q_.size()) {
            int tmp = max_q_.top();
            max_q_.pop();
            min_q_.push(tmp);
        }
        
        while (min_q_.size() - 1 > max_q_.size()) {
            int tmp = min_q_.top();
            min_q_.pop();
            max_q_.push(tmp);
        }
    }
    
    double findMedian() {
        if (max_q_.size() > min_q_.size()) return max_q_.top();
        else if (max_q_.size() < min_q_.size()) return min_q_.top();
        return (max_q_.top() + min_q_.top()) * 0.5;
    }

private:
    priority_queue<int, vector<int>, std::less<int>> max_q_;
    priority_queue<int, vector<int>, std::greater<int>> min_q_;
};

// uses a Balanced Binary Search Tree(AVL, multiset in c++)
// T(add) / T(remove) / T(search) / T(move pointers): logn, T(get max/min): O(1)(if implemented as vectors)
// uses two pointers to keep track of the middle two nums
// each time we insert a value, only needs to move ONE of the pointers ONE step
// T(get_median): O(1)
// T: O(nlogn). heap is for sure a perfect binary tree, while AVL generally is not that perfect,
// and it needs to do re-balancing all the time, so it is consistently slower than the heap solution.
// S: O(n)
class MedianFinder {
public:
    MedianFinder(): l_(s_.cend()), r_(s_.cend()) {}
    
    void addNum(int num) {
        s_.insert(num);
        if (s_.size() == 1) {
            l_ = r_ = s_.cbegin();
            return;
        }
        
        // case1: s_.size() even, e.g. [1 2(lr) 3 4*], 4 is the inserted
        // case2: s_.size() even, e.g. [0 1* 2(lr) 3], 0 is the inserted
        // when inserted num is equal with some existed num, c++ inserts it after it
        if (!(s_.size() & 1)) {
            if (num >= *r_) ++r_;
            else --l_;
        } else {
            // case3: s_.size() odd, e.g. [1(l) 2(r) 3*], 3 is the inserted
            // case4: s_.size() odd, e.g. [1(l) 1* 2(r)], 1 is the inserted, noted T(move pointers): logn, so we can only move r
            // case5: s_.size() odd, e.g. [0* 1(l) 2(r)], 1 is the inserted, same as case4
            if (num >= *r_) ++l_;
            else l_ = --r_;
        }
        
        return;
    }
    
    double findMedian() {
        if (!(s_.size() & 1)) return (*l_ + * r_) * 0.5;
        
        return *l_;
    }

private:
    multiset<int> s_;
    multiset<int>::const_iterator l_;
    multiset<int>::const_iterator r_;
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */