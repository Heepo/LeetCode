#include <vector>
#include <set>
#include <unordered_map>
using namespace std;

// FenwickTree, the same as BinaryIndexedTree(BIT)
// build tree T: O(nlogn), S: O(n)
// update one element T: O(logn)
// query T: O(logn)
class FenwickTree {
public:
    FenwickTree(vector<int>& nums): partial_sums(nums.size() + 1, 0) {
        for (int i = 0; i < nums.size(); ++i) {
            int j = i + 1;
            while (j < partial_sums.size()) {
                partial_sums[j] += nums[i];
                j += lowBit(j);
            } 
        }
    }
    
    void update(int index, int val) {
        // std::cout << "update val: " << val;
        ++index;
        while (index < partial_sums.size()) {
            // std::cout << " index: " << index << std::endl;
            partial_sums[index] += val;
            index += lowBit(index);
        }
    }
    
    int query(int index) {
        ++index;
        int sum = 0;
        // std::cout << "index: " << index;
        while (index > 0) {
            sum += partial_sums[index];
            index -= lowBit(index);
        }
        // std::cout << " sum: " << sum << std::endl;
        
        return sum;
    }

private:
    vector<int> partial_sums;
    
    inline int lowBit(int x) {
        return x & (-x);
    }
};

// iterates the array in reverse order
// keeps track of the appearance times of the number, and output the sum of the appearance times of the smaller ones
// once we sorted the array, we can do the prefix frequency sum on the sorted array
// the prefix sum time(i.e. query time) can reduce to O(logn)
// The intuition behind this solution is that, if we only do one-time prefix sum for an array, the time complexity must be at least O(n)
// But if we do multiple queries with updating operations now and then, there must be duplicated sum operations
// The Fenwick tree can deal with this dynamic prefix sum situations(uses dynamic programming when the array is fixed)
// The build time is O(nlogn) to get partial sums, and the update and the query time will be O(logn)
// Brute force time for multiple queries will be O(n^2)
class Solution {
public:
    vector<int> countSmaller(vector<int>& nums) {
        if (nums.empty()) return {};
        
        set<int> sorted(nums.begin(), nums.end());
        unordered_map<int, int> num_rank;
        int rank = 0;
        for (auto num: sorted) num_rank[num] = rank++;
        
        vector<int> ans;
        vector<int> freq(sorted.size(), 0);
        FenwickTree bit_freq(freq);
        for (int i = nums.size() - 1; i >= 0; --i) {
            ans.push_back(bit_freq.query(num_rank[nums[i]] - 1));
            bit_freq.update(num_rank[nums[i]], 1);
        }
        
        std::reverse(ans.begin(), ans.end());
        return ans;
    }
};