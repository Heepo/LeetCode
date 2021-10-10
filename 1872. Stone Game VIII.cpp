#include <vector>
#include <algorithm>
using namespace std;

// min-max problem
// define rolling status dp[i] as the diff when first player takes i stones and the opponent takes optimal number of stones(must > i).
// dp[i] = sum[0 : i) - max(dp[i + 1], ..., dp[n]), the max part means the opponent
// ans = max(dp[2], ... dp[n])
// T(sum): O(n), T(max_part) when calculating dp[n] first: O(n^2)
// S:O(n)
// the max part calculation still can be cached
// T: O(n)
// S: O(n), s(max_part): O(1)
class Solution {
public:
    int stoneGameVIII(vector<int>& stones) {
        const int n = stones.size();
        vector<int> sums = vector<int>(n + 1, 0);
        for (int i = 1; i <= n; ++i)
            sums[i] = sums[i - 1] + stones[i - 1];
        
        int max_ = sums[n]; // also dp[n]
        for (int i = n - 1; i >= 2; --i) {
            max_ = max(max_, sums[i] - max_);
        }
        
        return max_;
    }
};