// The i-th element will be moved to the [(i + k) % nums.size()]-th position.
// We can move the element from the start, then move the element on the target position, and so on, until all the elements are relocated.
// If n*k % nums.size() == 0 and n < nums.size(), then the process above can't relocate every element.
// Actually it means the greatest common divisor is not 1.
// T: O(n)
// S: O(1)
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        if (nums.size() <= 1 || k == 0) return;

        int origin_index = 0;
        int target_index = k % nums.size();
        int origin_temp = nums[origin_index];
        int target_temp = nums[target_index];
        int elements_left = nums.size();
        int gcd = greatest_common_divisor(nums.size(), k);
        // std::cout << "gcd: " << gcd << std::endl;
        while (elements_left > 0) {
            // If found went back to the start in a circle, shift right
            // There are gcd circles.
            if (gcd > 1 && elements_left < nums.size() && origin_index < gcd) {
                origin_index++;
                target_index = (origin_index + k) % nums.size();
                origin_temp = nums[origin_index];
                target_temp = nums[target_index];
            }

            target_temp = nums[target_index];
            nums[target_index] = origin_temp;
            origin_temp = target_temp;
            origin_index = target_index;
            target_index = (origin_index + k) % nums.size();
            target_temp = nums[target_index];
            --elements_left;

            // for (int i = 0; i < nums.size(); ++i) {
            //     std::cout << nums[i] << " ";
            // }
            // std::cout << std::endl;
        }

        return;
    }

    // The idea of this algorithm is, the GCD of two numbers doesn’t change if the smaller number is subtracted from the bigger number. 
    int greatest_common_divisor(int a, int b) {
        if (a == 0) return b;
        if (b == 0) return a;
        if (a == b) return a;
        else if (a > b) return greatest_common_divisor(a % b, b);
        else return greatest_common_divisor(a, b % a);
    }
};