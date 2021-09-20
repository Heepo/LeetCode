#include <vector>
#include <unordered_map>
#include <map>
using namespace std;

// uses BST(map), the starts are implicitly the min values of the BST
// T: O(nlogn)
// S: O(n)
class Solution1 {
public:
    bool isPossibleDivide(vector<int>& nums, int k) {
        if (nums.empty() || k == 0 || nums.size() % k != 0) return false;
        
        // T: O(nlogn), a BST, ordered by key
        map<int, int> num_count_m;
        for (auto num: nums) num_count_m[num]++;
        
        // T: O(n)
        while (!num_count_m.empty()) {
            auto it = num_count_m.begin();
            int start = it->first;
            int count = it->second;
            for (int i = 0; i < k; i++) {
                if (it->first != start + i || it->second < count) return false;
                it->second -= count;
                if (it->second == 0) num_count_m.erase(it);
                ++it;
            }
        }
        
        return true;
    }
};

// the consecutive limitation has provided a lot of order information
// uses hashmap + vector saving starts
// T: O(n)
// S: O(n)
class Solution2 {
public:
    bool isPossibleDivide(vector<int>& nums, int k) {
        if (nums.empty() || k == 0 || nums.size() % k != 0) return false;
        
        // T: O(n)
        unordered_map<int, int> num_count_m;
        for (auto num: nums) num_count_m[num]++;
        
        vector<int> starts;
        for (auto it: num_count_m)
            if (!num_count_m.count(it.first - 1)) starts.push_back(it.first);
        
        // T: O(n)
        while (!starts.empty()) {
            int start = starts.back();
            starts.pop_back();
            
            for (int i = k - 1; i >= 0; i--) {
                // no k consecutive numbers exist starting from start
                if (!num_count_m.count(start + i) || num_count_m[start + i] < num_count_m[start]) return false;
                num_count_m[start + i] -= num_count_m[start];
                
                // see if the next is a new start
                if (num_count_m[start + i] == 0) {
                    num_count_m.erase(start + i);
                    if (num_count_m.count(start + i + 1)) starts.push_back(start + i + 1);
                }
            }
        }
        
        return true;
    }
};