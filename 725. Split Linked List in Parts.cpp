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

class Solution {
public:
    vector<ListNode*> splitListToParts(ListNode* head, int k) {
        if (k == 1) return vector<ListNode*>{head};
        vector<ListNode*> ans;
        if (!head) {
            while (k--) ans.push_back(nullptr);
            return ans;
        }       
        
        int length = 0;
        ListNode* cur = head;
        while (cur) {
            length++;
            cur = cur->next;
        }
        
        int part_length = length / k;
        // the first one_more_num lists have part_length+1 elements
        int one_more_num = length % k;
        ListNode dummy(0);
        dummy.next = head;
        cur = head;
        ListNode* prev = &dummy;
        ans.push_back(cur);
        while (--k) {
            int count = part_length;
            if (one_more_num-- > 0) {
                count++;
            }
            while (count-- > 0) {
                prev = cur;
                cur = cur->next;
            }
            ans.push_back(cur);
            if (prev) prev->next = nullptr;
        }
        
        return ans;
    }
};