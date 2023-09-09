// Uses dynamic programming in rolling array way.
// Calculates the maximum reaching position until i-th element. Only when the current position can be reached, then we can jump from it.
// Once the maximum reaching position is beyond the last index, we can return the result to prune this process.
// T: Upper bound is O(n).
// S: O(1).
class Solution {
public:
    bool canJump(vector<int>& nums) {
        if (nums.size() <= 1) return true;

        int max_reaching_index = 0;
        for (int i = 0; i < nums.size(); ++i) {
            if (max_reaching_index >= i) {
                if (nums[i] + i > max_reaching_index) max_reaching_index = nums[i] + i;
            }
            else return false; // If current position is unreachable, so as the final index.

            if (max_reaching_index >= nums.size() - 1) {
                return true;
            }
        }
        return false;
    }
};