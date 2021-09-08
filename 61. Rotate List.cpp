// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k) {
        if (k <= 0 || !head || !head->next) {
            return head;
        }
        
        int length = 0;
        ListNode* tail = head;
        ListNode* cur = head;
        while (cur) {
            tail = cur;
            cur = cur->next;
            length++;
        }
        
        if (k % length == 0) {
            return head;
        }
        
        ListNode* new_tail = new ListNode(0);
        new_tail->next = head;
        cur = head;
        int n = length - (k % length);
        while (n-- > 0) {
            cur = cur->next;
            new_tail = new_tail->next;
        }
        tail->next = head;
        head = cur;
        new_tail->next = nullptr;
        
        return head;
    }
};