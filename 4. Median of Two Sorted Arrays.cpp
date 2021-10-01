#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        // enusres nums1.size() < nums2.size()
        if (nums2.size() < nums1.size()) return findMedianSortedArrays(nums2, nums1);
        
        if (nums1.empty()) {
            if (nums2.size() % 2 == 0) return (nums2[nums2.size() / 2 - 1] + nums2[nums2.size() / 2]) * 0.5;
            else return nums2[nums2.size() / 2];
        }
        
        // prevents overflow
        int left_num = nums1.size() + (nums2.size() - nums1.size() + 1) / 2;
        
        // does binary search on nums1, find the split postion i
        // elements before i all belong to the left part, and it also equals with the size of left part of nums1
        // possible postions are range from 0 to nums1.size(), i.e. no elements to all elements can be chosen
        int l = 0;
        int r = nums1.size();
        while (l < r) {
            // left part size of nums1
            int i = l + (r - l) / 2;
            // left part size of nums2
            int j = left_num - i;
            
            // there has to be one and only median split point
            // because nums[i + 1] >= nums[i] && nums2[j - 2] <= nums2[j - 1], i must be more qualified
            // searches l to i
            if (nums1[i] >= nums2[j - 1])
                r = i;
            // i can't be chosen
            else
                l = i + 1;
            
            // quicker exit condition
            if (i >= 1 && i < nums1.size() && j >= 1 && j < nums2.size() &&
                nums1[i] >= nums2[j - 1] && nums2[j] >= nums1[i - 1]) {
                l = i;
                break;
            }
        }
        
        // now l is the split point of nums1
        int k = left_num - l;
        int left_max = std::max(l <= 0 ? INT_MIN : nums1[l - 1],
                                k <= 0 ? INT_MIN : nums2[k - 1]);
        // std::cout << "left_max: " << left_max << std::endl;
        if ((nums1.size() + nums2.size()) % 2 != 0) return left_max;
        
        int right_min = std::min(l >= nums1.size() ? INT_MAX : nums1[l],
                                 k >= nums2.size() ? INT_MAX : nums2[k]);
        // std::cout << "right_min: " << right_min << std::endl;
        return (left_max + right_min) * 0.5;
    }
};