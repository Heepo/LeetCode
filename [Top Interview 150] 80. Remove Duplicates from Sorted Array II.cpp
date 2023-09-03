// Iterates over nums and uses 'k' to store the number of elements that satisfy the condition. Each new element that meets the condition is moved to the k-th position.
// T: O(n)
// S: O(1)
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if (nums.empty()) return 0;
        if (nums.size() == 1) return 1;

        int appearance_time = 1;
        int k = 1;
        for (int i = 1; i < nums.size(); ++i) {
            if (nums[i] != nums[i - 1]) {
                appearance_time = 1;
                if (i > k) nums[k] = nums[i];
                ++k;
            } else {
                // this element is still satisfied
                if (++appearance_time == 2) {
                    if (i > k) nums[k] = nums[i];
                    ++k;
                }
            }
        }

        return k;
    }
};