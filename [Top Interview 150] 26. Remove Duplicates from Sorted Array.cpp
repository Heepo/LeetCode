// Iterates over nums and compares the current element with its previous element to check for duplicates.
// We can count the unique element number as 'k'; each new unique element can be moved to the (k-1)th position.
// T: O(n)
// S: O(1)
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if (nums.empty()) return 0;
        if (nums.size() == 1) return 1;

        int unique_count = 1;
        for (int i = 1; i < nums.size(); ++i) {
            if (nums[i] != nums[i-1]) {
                if (i > unique_count) nums[unique_count] = nums[i];
                unique_count++;
            }
        }

        return unique_count;
    }
};