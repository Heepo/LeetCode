#include <unordered_set>
using namespace std;

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// S: O(n)
class Solution1 {
public:
    ListNode *detectCycle(ListNode *head) {
        if (!head) return nullptr;
        
        ListNode* cur = head;
        unordered_set<ListNode*> s;
        while (cur) {
            if (s.count(cur)) return cur;
            s.insert(cur);
            cur = cur->next;
        }
        
        return nullptr;
    }
};

class Solution2 {
public:
    ListNode *detectCycle(ListNode *head) {
        if (head == nullptr) {
            return nullptr;
        }
        
        ListNode* slow = head;
        ListNode* fast = head;
        while (fast) {
            if (!fast->next) return nullptr;
            
            fast = fast->next->next;
            slow = slow->next;
            
            // when they meet, we assumes the length before the circle is p, the meeting point - the circle point is x, the circle
            // length is q. Then 2(p + x) = p + x + nq. So x + p = nq. From the meeting point, move p steps, that's the circle entry.
            if (fast == slow) {
                slow = head;
                while (fast != slow) {
                    fast = fast->next;
                    slow = slow->next;
                }
                return fast;
            }
        }
        return nullptr;
    }
};