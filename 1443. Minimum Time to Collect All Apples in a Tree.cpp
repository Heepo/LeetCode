#include <vector>
using namespace std;

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// T: O(n) each node will be visited once
// S: O(n) for building graph and visited marks and the recursion stack
class Solution {
public:
    int minTime(int n, vector<vector<int>>& edges, vector<bool>& hasApple) {
        // when the subtree of a child or the child itself has apple, it needs to be visited to collect apples
        // so either way the cost += 2
        if (edges.empty() || hasApple.empty()) return 0;
        
        // builds the adjacency list undirected graph
        vector<vector<int>> g_(edges.size()+1, vector<int>{});
        for (auto edge: edges) {
            g_[edge[0]].push_back(edge[1]);
            g_[edge[1]].push_back(edge[0]);
        }
    
        vector<int> visited(edges.size()+1, 0);
        
        return dfs_(g_, hasApple, visited, 0);
    }
    
    int dfs_(vector<vector<int>>& g_, vector<bool>& hasApple, vector<int>& visited, int node) {
        int cost = 0;
        visited[node] = 1;
        
        for (int child: g_[node]) {
            if (visited[child])
                continue;
            
            // only when the subtree of the child or the child itself has apple then needs to be visited recursively
            int sub_cost = dfs_(g_, hasApple, visited, child);
            if (sub_cost || hasApple[child])
                cost += sub_cost + 2;
        }
        
        return cost;
    }
};