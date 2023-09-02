// Uses two pointers for each element of the array.
// Then iterate backward from both ends of the two arrays, selecting the larger element until all the elements of nums2 are settled.
// T: O(m + n)
// S: O(1)
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        if (nums1.empty() || nums2.empty() || nums1.size() != m + n || nums2.size() != n) return;

        int nums1_index = m - 1;
        int nums2_index = n - 1;
        int move_target_index = m + n - 1;

        while (nums2_index >= 0) {
            // If nums1 runs out of elements, simply move the remaining elements of nums2 to the front positions; there is no need to compare.
            if (nums1_index >= 0 && nums1[nums1_index] > nums2[nums2_index]) {
                nums1[move_target_index--] = nums1[nums1_index--];
            }
            else {
                nums1[move_target_index--] = nums2[nums2_index--];
            }

        }

        return;
    }
};