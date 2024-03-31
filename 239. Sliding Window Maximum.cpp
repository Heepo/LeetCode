#include <deque>

// Uses a monotonic queue to store potential maximum values.
// Noted that this differs from sorting the values inside the window because we maintain only
// the monotonic values and discard those that do not satisy this attribute, instead of keeping
// and sorting with others. Thus, the time complexity of processing the monotonic queue is
// amortized O(1) for each sliding operation.
// T: O(n)
// S: O(1)

class MonotonicQueue {
public:
    void push(int value) {
        // If the value is larger than those in the queue, it implies those values cannot be maximum
        // when in the same window, and they are popped out. Thus, this monotonic queue maintains
        // a decreasing order.
        while (!_dq.empty() && _dq.back() < value) _dq.pop_back();

        _dq.emplace_back(value);
    }

    void pop() {
        // The order is not only monotonic but also the same as the order of nums.
        // Alawys pop the leftmost element, which is also the maxmimum value.
        _dq.pop_front();
    }

    int max() {
        return _dq.front();
    }

private:
    std::deque<int> _dq;
};

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> res;
        if (nums.empty() || k == 0 || k > nums.size()) return res;

        // This monotonic queue is a part of the sliding window, which only contains some monotonic values.
        MonotonicQueue window;
        for (int i = 0, j = 0; i < nums.size() - k + 1, j < nums.size(); ++i) {
            while (j - i < k) window.push(nums[j++]);
            res.emplace_back(window.max());
            // If nums[i] is smaller than other elements in the window, then it has already been popped.
            if (window.max() == nums[i]) window.pop();
        }

        return res;
    }
};

class Solution2 {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> answer;
        if (nums.empty() || k == 0 || k > nums.size()) return answer;

        // Uses deque to simulate a monotonic queue for storing indices of monotonic values within the sliding window.
        std::deque<int> monotonic_indices;
        for (int i = 0; i < nums.size(); ++i) {
            // Each time a new value is encountered, it's first pushed onto the queue. Then, we evaluate whether the
            // sliding window exceeds its designated size.
            while (!monotonic_indices.empty() && nums[monotonic_indices.back()] < nums[i]) monotonic_indices.pop_back();
            monotonic_indices.emplace_back(i);

            // The sliding window has already formed a full window.
            if (i - k + 1 >= 0) answer.emplace_back(nums[monotonic_indices.front()]);

            // Examines the size of the sliding window.
            if (monotonic_indices.front() == i - k + 1) monotonic_indices.pop_front();
        }

        return answer;
    }
};