#include <string>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;

// expands the graph as a duplicated nodes tree
// sorts the children and uses the post-order traversal. The reverse of the result is the answer
// T:O(nlogn) for the sort
// S:O(n)
class Solution {
public:
    vector<string> findItinerary(vector<vector<string>>& tickets) {
        for (auto ticket: tickets) g_[ticket[0]].push_back(ticket[1]);
        
        // sorts the children
        for (auto& node: g_) {
            auto& dests = node.second;
            sort(dests.begin(), dests.end());
        }
        
        vector<string> ans;
        string start = "JFK";
        
        visit(start, ans);
        std::reverse(ans.begin(), ans.end());
        
        return ans;
    }

private:
    unordered_map<string, deque<string>> g_;
    
    void visit(string& start, vector<string>& ans) {
        // std::cout << start << std::endl;
        while (!g_[start].empty()) {
            string front = g_[start].front();
            g_[start].pop_front();
            visit(front, ans);
        }
        
        ans.push_back(start);
        return;
    }
};