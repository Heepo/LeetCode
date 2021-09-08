#include <iostream>
#include <utility>

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
    ListNode* sortList(ListNode* head) {
        // bottom-up merge sort
        if (!head || !head->next) return head;
        
        // uses O(n) time to acquire the length of the list
        int length = 0;
        ListNode dummy(0);
        dummy.next = head;
        ListNode* cur = &dummy;
        while (cur->next) {
            length++;
            cur = cur->next;
        }
        
        for (int n = 1; n < length; n <<= 1) {
            merge_sort(dummy, n);
            // print_list(dummy.next);
        }
        
        return dummy.next;
    }
    
    // breaks to parts of max_length equals with n, and merge sorts adjacent two parts
    void merge_sort(ListNode& dummy, int n) {
        ListNode* cur = dummy.next;
        ListNode* fore_tail = &dummy;
        while (cur) {
            ListNode* r_head = break_list(cur, n);
            ListNode* rest_head = break_list(r_head, n);
            // returns the head and the tail of merged list
            auto merged = merge(cur, r_head);
            // print_list(merged.first);
            fore_tail->next = merged.first;
            fore_tail = merged.second;
            fore_tail->next = rest_head;
            cur = rest_head;
        }
        return;
    }
    
    ListNode* break_list(ListNode* cur, int n) {
        if (!cur) return cur;
        
        ListNode* tail = cur;
        while (n-- > 0 && cur) {
            tail = cur;
            cur = cur -> next;
        }
        tail->next = nullptr;
        
        return cur;
    }
    
    std::pair<ListNode*, ListNode*> merge(ListNode* l1, ListNode* l2) {
        ListNode dummy(0);
        ListNode* tail = &dummy;
        ListNode* cur = &dummy;
        while (l1 && l2) {
            if (l1->val > l2->val) std::swap(l1, l2);
            cur->next = l1;
            cur = cur->next;
            l1 = l1->next;
        }
        
        if (l1) cur->next = l1;
        if (l2) cur->next = l2;
        
        while (cur->next) cur = cur->next;
        tail = cur;
        
        return std::make_pair(dummy.next, tail);
    }
    
    void print_list(ListNode* head) {
        while (head) {
            std::cout << head->val << " ";
            head = head->next;
        }
        std::cout << std::endl;
        return;
    }
};