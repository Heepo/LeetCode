// Moore Voting Algorithm
// Initialize a candidate with the first element and set a counter to 1. Iterate over the 'nums'. If it encounters a different element, decrease the counter by 1; otherwise, increase it by 1. Once the counter reaches 0, set the candidate to the new element and reset the counter to 1. The final candidate will be the majority element. Iterating over the 'nums' again will confirm whether there is a majority element.
// Majority Element Survival: If there is a majority element, it will always survive the process and end up as the candidate. This is because it appears more than 'n/2' times, and all other elements combined appear less than 'n/2' times.
// That means only the counter of the majority element will never reach zero.
// T: O(n)
// S: O(1)

class Solution {
public:
    int majorityElement(vector<int>& nums) {
        if (nums.size() == 1) return nums[0];

        int candidate = nums[0];
        int counter = 1;
        for (int i = 1; i < nums.size(); ++i) {
            if (nums[i] != candidate) --counter;
            else ++counter;

            if (counter == 0) {
                candidate = nums[i];
                counter = 1; // Only the counter of the majority element can always bounce back
            }
        }

        return candidate;
    }
};