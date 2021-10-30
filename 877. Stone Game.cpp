#include <vector>
#include <algorithm>
using namespace std;

// min-max problem
// defines dp[i, j] as the winning number when only left i ~ j
// dp[i, j] = max(piles[i] - dp[i + 1, j], piles[j] - dp[i, j - 1]);
// Only the right-above half of dp needs to be calculated
// all kinds of (i, j) should be calculated, but they need to be memorized, or else duplicate calculations will be made
// T: O(n^2)
// S: O(n^2)
class Solution {
public:
    bool stoneGame(vector<int>& piles) {
        vector<vector<int>> dp = vector<vector<int>>(piles.size(), vector<int>(piles.size(), -1));
        
        return stoneGame_(piles, dp, 0, piles.size() - 1) > 0;
    }
    
private:
    int stoneGame_(vector<int>& piles, vector<vector<int>>& dp, int l, int r) {
        if (l == r) {
            dp[l][l] = piles[l];
            return dp[l][l];
        }
        
        if (dp[l][r] > -1)
            return dp[l][r];
        
        dp[l][r] =  max(piles[l] - stoneGame_(piles, dp, l + 1, r),
                       piles[r] - stoneGame_(piles, dp, l, r - 1));
                       
        return dp[l][r];
    }
};

// Non-recursive solution
// Calculations start from the diagonals ascending
// T: O(n^2)
// S: O(n^2)
class Solution {
public:
    bool stoneGame(vector<int>& piles) {
        vector<vector<int>> dp = vector<vector<int>>(piles.size(), vector<int>(piles.size(), -1));
        
        for (int interval = 0; interval < piles.size(); ++interval) {
            for (int start = 0; start + interval < piles.size(); ++ start) {
                if (interval == 0)
                    dp[start][start + interval] = piles[start];
                else
                    dp[start][start + interval] = max(piles[start] - dp[start + 1][start + interval],
                                                      piles[start + interval] - dp[start][start + interval - 1]);
            }
        }
        
        return dp[0][piles.size() - 1] > 0;
    }
    
};