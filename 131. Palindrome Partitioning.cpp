#include <vector>
using namespace std;

class Solution {
public:
    vector<vector<string>> partition(string s) {
        vector<vector<string>> res;
        if (s.length() == 0) {
            return res;
        }
        if (s.length() == 1) {
            vector<string> res_(1, s);
            res.push_back(res_);
            return res;
        }
        
        vector<vector<int>> dp(s.length(), vector<int>(s.length(), -1));
        res = partition_(s, 0, s.length() - 1, dp);  
        
        return res;
    }
    
    vector<vector<string>> partition_(string& s, int start, int end, vector<vector<int>>& dp) {
        vector<vector<string>> res;
        if (start < 0 || end >= s.length()) {
            return res;
        }
        if (start == end) {  
            vector<string> palindromes(1, s.substr(start, 1));
            res.push_back(palindromes);
            return res;
        }
        if (start == end - 1) {
            vector<string> palindromes;
            palindromes.push_back(s.substr(start, 1));
            palindromes.push_back(s.substr(start + 1, 1));
            res.push_back(palindromes);
            if (s[start] == s[end]) {
                palindromes.clear();
                palindromes.push_back(s.substr(start, 2));
                res.push_back(palindromes);
            }
            
            return res;
        }
        
        for (int i = start; i <= end; i++) {
            //std::cout << s.substr(start, i - start + 1) << " " << isPalindrome(s, start, i, dp) << std::endl;
            if (isPalindrome(s, start, i, dp)) {
                if (i == end) {
                    vector<string> partial_res;
                    partial_res.push_back(s.substr(start, i - start + 1));
                    res.push_back(partial_res);
                    break;
                }
                vector<vector<string>> partial_res = partition_(s, i + 1, end, dp);
                for (auto v: partial_res) {
                    v.insert(v.begin(), s.substr(start, i - start + 1));
                    res.push_back(v);
                }
            }
        }
        
        return res;
    }
    
    bool isPalindrome(string& s, int start, int end, vector<vector<int>>& dp) {
        if (start == end) {
            dp[start][end] = 1;
            return true;
        }
        if (start == end - 1) {
            if (s[start] == s[end]) {
                dp[start][end] = 1;
                return true;
            } else {
                dp[start][end] = 0;
                return false;
            }
        }
        
        if (dp[start][end] == 1) {
            return true;
        } else if (dp[start][end] == 0) {
            return false;
        } else {
            if (s[start] != s[end]) {
                dp[start][end] = 0;
                return false;
            } else {
                return isPalindrome(s, start + 1, end - 1, dp);
            }
        }
        
    }

};