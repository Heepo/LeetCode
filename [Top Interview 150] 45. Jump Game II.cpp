// Uses dynamic programming.
// We can solve the sub-problem backward from the end of the nums.
// Because it's easier to determine the min jumping time to the end for the elements.
// Once an element can't jump directly to the end, its min jumping time is the min jumping time of the reachable elements plus 1.
// T: O(n)
// S: O(kn), k is the max value of the elements.
class Solution {
public:
    int jump(vector<int>& nums) {
        if (nums.size() <= 1) return 0;

        // In case when nums[i] == 0, dp[i] won't be updated and will lead to dp[i] + 1 getting overflowed.
        vector<int> dp(nums.size(), INT_MAX - 1);
        dp[nums.size() - 1] = 0;
        for (int i = nums.size() - 2; i >= 0; --i) {
            if (i + nums[i] >= nums.size() - 1) dp[i] = 1;
            else {
                for (int j = 1; j <= nums[i]; ++j) {
                    dp[i] = std::min(dp[i], dp[i + j] + 1);
                }
            }
        }
        return dp[0];
    }
};