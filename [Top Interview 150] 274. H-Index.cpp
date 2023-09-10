// First we sort the citations. Then we iterate backward from the end of ciations.
// As the iteration step grows, and if the citation is larger or equal to the steps, that means the h-index is at least the number of the steps.
// T: O(nlogn).
// S: O(n), using merge sort.
class Solution {
public:
    int hIndex(vector<int>& citations) {
        if (citations.empty()) return 0;
        if (citations.size() == 1) {
            if (citations[0] >= 1) return 1;
            return 0;
        }

        merge_sort(citations, 0, citations.size() - 1);
        
        int hindex = 0;
        for (int i = citations.size() - 1; i >= 0; --i) {
            // There are already hindex papers whose citations are at least hindex.
            if (citations[i] > hindex) ++hindex;
            else return hindex;
        }

        return hindex;
    }

    void merge_sort(vector<int>&nums, int l, int r) {
        if (l >= r) return;
        int mid = (l + r) / 2;
        merge_sort(nums, l, mid);
        merge_sort(nums, mid + 1, r);
        // print_vector(nums);

        combine(nums, l, mid, r);
        // print_vector(nums);
        return;
    }

    void combine(vector<int>&nums, int l, int mid, int r) {
        int i = l;
        int j = mid + 1;
        vector<int> combined(r - l + 1, 0);
        int k = 0;
        while (i <= mid && j <= r) {
            if (nums[i] <= nums[j]) combined[k++] = nums[i++];   
            else combined[k++] = nums[j++];
        }

        while (i <= mid) combined[k++] = nums[i++];
        while (j <= r) combined[k++] = nums[j++];

        for (k = 0; k <= r - l; ++k) {
            nums[l + k] = combined[k];
        }

        return;
    }
};