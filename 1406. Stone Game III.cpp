#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// min-max probelm
// defines dp[i] as starting from i, the max diff
// dp[i] = max(stoneValue[i] - dp[i+1], stoneValue[i,i+1] - dp[i+2], stoneValue[i,i+2] - dp[i+3])
// uses three holders to store
// T: O(n)
// S: O(1)
class Solution {
public:
    string stoneGameIII(vector<int>& stoneValue) {
        if (stoneValue.empty()) return "Tie";
        
        vector<int> dp = vector<int>(4, 0);
        
        for(int i = stoneValue.size() - 1; i >= 0; --i) {
            dp[0] = max(stoneValue[i] - dp[1],
                        max(
                            (i+1 >= stoneValue.size()) ? INT_MIN : (stoneValue[i+1] + stoneValue[i] - dp[2]),
                            (i+2 >= stoneValue.size()) ? INT_MIN : (stoneValue[i+2] + stoneValue[i+1] + stoneValue[i]- dp[3]))
                        );
            dp[3] = dp[2];
            dp[2] = dp[1];
            dp[1] = dp[0];
            // std::cout << dp[0] << " " << dp[1] << " " << dp[2] << " " << dp[3] << std::endl;
        }
        
        if (dp[0] > 0) return "Alice";
        else if (dp[0] == 0) return "Tie";
        return "Bob";
    }
};