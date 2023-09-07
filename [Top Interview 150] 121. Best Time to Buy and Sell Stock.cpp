// Iterates over the prices to keep track of the min price until (i-1)-th day and the max profit.
// This is a 1-d dynamic programming implementation using a rolling array.
// Note that the selling should occur on a different day after the buying.
// T: O(n)
// S: O(1)
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.size() <= 1) return 0;

        int min_price = INT_MAX;
        int max_profit = 0;
        for (int i = 0; i < prices.size(); ++i) {
            max_profit = std::max(prices[i] - min_price, max_profit);
            min_price = std::min(min_price, prices[i]); // only for next day using
        }

        return max_profit;
    }
};