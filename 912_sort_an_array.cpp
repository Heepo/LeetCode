#include <vector>
#include <random>
#include <algorithm>
using namespace std;
class Solution {
public:
    vector<int> sortArray(vector<int>& nums) {
        if (nums.size() <= 1) {
            return nums;
        }
        
        mergeSort(nums, 0, nums.size());
        std::shuffle(nums.begin(), nums.end(), nums); 
        quickSort(nums, 0, nums.size() - 1);
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

    void quickSort(vector<int>& nums, int start, int end) {
        if (start >= end) {
            return;
        }
        
        int pivot = partition(nums, start, end);
        quickSort(nums, start, pivot - 1);
        quickSort(nums, pivot + 1, end);
    }
    
    // 5 3 2 5 6 2 9 1
    // 5 3 2 5 (6) 2 9 1 -> 5 3 2 5 (2) 6 9 1
    // 5 3 2 5 2 (6) 9 1 -> 5 3 2 5 2 (1) 9 6
    // 5 3 2 5 2 1 9 6 -> 1 3 2 5 2 | 5 | 9 6
    int partition(vector<int>& nums, int start, int end) {
        int pivot = nums[start];
        int first_larger_index = end + 1;
        for (int i = start; i <= end; i++) {
            if (first_larger_index == end + 1 && nums[i] > pivot) {
                first_larger_index = i;
                break;
            }
        }
        
        for (int i = first_larger_index; i <= end; i++) {
            if (nums[i] < pivot) {
                swap(nums, first_larger_index, i);
                first_larger_index++;
            }
        }
        
        swap(nums, start, first_larger_index - 1);
        
        return first_larger_index - 1;
    }
    
    void swap(vector<int>& nums, int i, int j) {
        int tmp = nums[i];
        nums[i] = nums[j];
        nums[j] = tmp;
        return;
    }
};