// Iterates over nums and swaps each element equal to val with an element from the tail that is not equal to val.
// T: O(n)
// O: O(1)
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        if (nums.empty()) return 0;

        int left = 0;
        int right = nums.size() - 1;
        while (right > left) {
            if (nums[left] != val) left++;
            else {
                if (nums[right] == val) {
                    right--;
                } else {
                    swap(nums, left, right);
                    left++;
                    right--;
                }
            }
        }

        if (nums[right] == val) return right;
        return right + 1;
    }

    void swap(vector<int>& nums, int left, int right) {
        if (nums.empty() || left < 0 || right < 0 || left >= nums.size() || right >= nums.size() || left == right) return;

        int temp = nums[left];
        nums[left] = nums[right];
        nums[right] = temp;
        return;
    }
};