#include<vector>
using namespace std;
class Solution {
public:
    vector<int> sortArray(vector<int>& nums) {
        // merge sort
        if (nums.size() <= 1) {
            return nums;
        }
        
        mergeSort(nums, 0, nums.size());
        return nums;
    }
    
    void mergeSort(vector<int>& nums, int left, int right) {
        //std::cout << "right: " << right << " left: " << left << std::endl;
        if (right - left <= 1) {
            return;
        }
        
        int mid = (right + left) / 2;
        //std::cout << "mid: " << mid << std::endl;
        // sort left & right
        mergeSort(nums, left, mid);
        mergeSort(nums, mid, right);
        
        // [2, 3] [0, 1, 2]
        vector<int> merged;
        int i = left;
        int j = mid;
        while (i < mid && j < right) {
            //std::cout << "left: " << left << " mid: " << mid << " right: " << right << std::endl;
            //std::cout << "i: " << i << " j: " << j << std::endl;
            if (nums[i] > nums[j]) {
                merged.push_back(nums[j]);
                j++;
            } else {
                merged.push_back(nums[i]);
                i++;
            }
        }
        if (i < mid) {
            for (int k = i; k < mid; k++) {
                merged.push_back(nums[k]);
            }
        }
        if (j < right) {
            for (int k = j; k < right; k++) {
                merged.push_back(nums[k]);
            }
        }
        for (int k = 0; k < merged.size(); k++) {
            nums[left + k] = merged[k];
            //std::cout << "left + k: " << left + k << " merged[k]: " << merged[k] << std::endl;
        }
        
        return;
    }
};