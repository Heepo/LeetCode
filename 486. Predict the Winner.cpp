#include <vector>
#include <algorithm>
using namespace std;

// recursion with memory(DP)
// T: O(n^2) n^2 sub problems
// S: O(n^2)
class Solution {
public:
    bool PredictTheWinner(vector<int>& nums) {
        if (nums.empty()) return true;
        
        mem_ = vector<int>(nums.size() * nums.size(), 0);
        
        return getScoreDiff_(nums, 0, nums.size() - 1) >= 0;
    }

private:
    // remembers the score diff
    vector<int> mem_;
    
    int getScoreDiff_(vector<int>& nums, int l, int r) {
        if (l == r) return nums[l];
        
        if (mem_[l * nums.size() + r] > 0) return mem_[l * nums.size() + r];
        
        // after player 1 makes a choice, player 2 uses same strategy to choose smartly from rest of the array
        // so here the operation should be minus
        mem_[l * nums.size() + r] = max(nums[l] - getScoreDiff_(nums, l + 1, r),
                                        nums[r] - getScoreDiff_(nums, l, r - 1));
        
        return mem_[l * nums.size() + r];
    }
};