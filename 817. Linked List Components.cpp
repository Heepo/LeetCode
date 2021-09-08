#include <unordered_set>
#include <unordered_map>
#include <vector>
using namespace std;

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution1 {
public:
    // T: O(n) S: O(n)
    int numComponents(ListNode* head, vector<int>& nums) {
        if (!head) return 0;
        if (!head->next) return 1;
        
        unordered_set<int> nodes(nums.begin(), nums.end());
        unordered_map<int, vector<int>> adj;
        ListNode* cur = head;
        while (cur->next) {
            if (nodes.count(cur->val) && nodes.count(cur->next->val)) {
                adj[cur->val].push_back(cur->next->val);
                adj[cur->next->val].push_back(cur->val);
            }
            cur = cur->next;
        }
        // for (int num: nums) {
        //     std::cout << "num: " << num << " adj: ";
        //     for (int adj_: adj[num]) std::cout << adj_ << " ";
        //     std::cout << std::endl;
        // }
        
        int ans = 0;
        unordered_set<int> visited;
        for (int num: nums) {
            if (!visited.count(num)) {
                ans++;
                dfs(adj, num, visited);
            }
        }
        
        return ans;
    }
    
    void dfs(unordered_map<int, vector<int>>& adj, int num, unordered_set<int>& visited) {
        visited.insert(num);
        for (int adj_: adj[num]) {
            if (!visited.count(adj_)) {
                visited.insert(adj_);
                dfs(adj, adj_, visited);
            }
        }
        
        return;
    }
};

class Solution2 {
public:
    // T: O(n) S: O(n)
    int numComponents(ListNode* head, vector<int>& nums) {
        if (!head) return 0;
        if (!head->next) return 1;
        
        unordered_set<int> nodes(nums.begin(), nums.end());
        ListNode* cur = head;
        int ans = 0;
        //    0->1->2->3->4->nullptr; [0 3 1 4]
        //    o  o  x  o  o  x
        //ans    1        2
        while (cur) {
            if (nodes.count(cur->val) && (!cur->next || !nodes.count(cur->next->val))) ans++;
            cur = cur->next;
        }
        
        return ans;
    }
};