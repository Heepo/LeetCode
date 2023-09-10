#include <vector>
#include <random>
#include <algorithm>
using namespace std;
// borrows implemented min_heap, while max heap is more suitable
class MinHeap {
public:
    vector<int> min_heap;
    
    // builds a heap O(n)
    MinHeap(vector<int>& data) {
        this->min_heap = data;
        for (int i = (this->min_heap.size() - 1) / 2; i >= 0; i--) {
            this->heapify_down(i);
        }
    }
    
    // O(nlog(n))
    vector<int> heap_sort() {
        vector<int> res;
        while (!this->min_heap.empty()) {
            res.push_back(this->top());
            this->pop();
        }
        return res;
    }
    
    void push(int node) {
        this->min_heap.push_back(node);
        this->heapify_up(this->min_heap.size() - 1);
    }
    
    int top() {
        return this->min_heap.front();
    }
    
    void pop() {
        this->min_heap[0] = this->min_heap[this->min_heap.size() - 1];
        this->min_heap.pop_back();
        this->heapify_down(0);
    }
    
    bool empty() {
        return this->min_heap.empty();
    }
    
private:
    // O(log(n))
    void heapify_up(int i) {
        if (i == 0) {
            return;
        }
        int parent = (i - 1) / 2;
        if (this->min_heap[parent] > this->min_heap[i]) {
            this->swap(parent, i);
            heapify_up(parent);
        }
        
        return;
    }
    
    // O(log(n)), if the parent is larger than one of the children, then the parent goes down
    void heapify_down(int i) {
        int l = 2 * i + 1;
        int r = 2 * i + 2;
        if (l >= this->min_heap.size()) return;
        if (r >= this->min_heap.size()) {
            if (this->min_heap[l] < this->min_heap[i]) this->swap(i, l);
            return;
        }
        
        int min = (this->min_heap[l] < this->min_heap[r]) ? l : r;
        if (this->min_heap[min] < this->min_heap[i]) {
            this->swap(i, min);
            heapify_down(min);
        }
        
        return;
    }
    
    void swap(int i, int j) {
        int tmp = this->min_heap[i];
        this->min_heap[i] = this->min_heap[j];
        this->min_heap[j] = tmp;
    }
};

class Solution {
public:
    vector<int> sortArray(vector<int>& nums) {
        if (nums.size() <= 1) {
            return nums;
        }
        
        // merge_sort(nums, 0, nums.size() - 1);
        // std::random_shuffle(nums.begin(), nums.end());
        // quickSort(nums, 0, nums.size() - 1);
        
        // return nums;
        
        // here borrows the implemented min heap, while using the max heap is more straightforward
        MinHeap q(nums);
        return q.heap_sort();
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
    
    void swap(vector<int>& nums, int i, int j) {
        int tmp = nums[i];
        nums[i] = nums[j];
        nums[j] = tmp;
        return;
    }

    void print_vector(vector<int>& nums) {
        for (auto num: nums) std::cout << num << " ";
        std::cout << std::endl;
    }
};