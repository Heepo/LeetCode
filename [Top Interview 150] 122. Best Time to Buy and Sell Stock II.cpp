// Every day we have three choices: buy, sell, or skip (do nothing). Therefore, the upper bound of the brute force method is O(3^n).
// An important note here is that we don't need to remember the lowest price before the i-th day when selling.
// We only need to know the max profit, not the exact days when transactions occur. Thus, we can maintain the balance; buying and selling can just subtract or add to the balance.
// On the i-th day, if we want to sell, we should hold a share first, then we can add prices[i] to the balance.
// If we want to buy a share, we must not hold a share at the moment, then we can subtract prices[i] from the balance. This purchase is for future selling, or else this transaction will just be losing money.
// Therefore, we can maintain two kinds of balances to distinguish whether we hold a share at the moment or not.
// T: O(n)
// S: O(n). For every position, we maintain two kinds of balances.
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.size() <= 1) return 0;

        int balance_no_holding = 0;
        int balance_holding = INT_MIN; // illegal state
        dp(prices, prices.size() - 1, balance_no_holding, balance_holding);

        // balance_no_holding is surely larger than balance_holding.
        return balance_no_holding;
    }

    void dp(const vector<int>& prices, int i, int& balance_no_holding, int& balance_holding) {
        if (i == -1) {
            balance_no_holding= 0;
            balance_holding = INT_MIN;
            return;
        }

        dp(prices, i - 1, balance_no_holding, balance_holding);
        balance_no_holding = std::max(balance_no_holding, balance_holding + prices[i]); // skip or sell
        balance_holding = std::max(balance_holding, balance_no_holding - prices[i]); // skip or buy
        return;
    }
};