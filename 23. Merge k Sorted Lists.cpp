#include <vector>
#include <queue>
using namespace std;

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class MinHeap {
public:
    vector<ListNode*> min_heap;
    
    MinHeap(){}
    
    // builds a heap cost O(n) (can be proved)
    MinHeap(vector<ListNode*>& data) {
        this->min_heap = data;
        for (int i = (this->min_heap.size() - 1) / 2; i >= 0; i--) {
            this->heapify_down(i);
        }
    }
    
    void push(ListNode* node) {
        this->min_heap.push_back(node);
        this->heapify_up(this->min_heap.size() - 1);
    }
    
    ListNode* top() {
        return this->min_heap.front();
    }
    
    void pop() {
        this->min_heap[0] = this->min_heap[this->min_heap.size() - 1];
        this->min_heap.pop_back();
        this->heapify_down(0);
    }
    
    bool empty() {
        return this->min_heap.empty();
    }
    
private:
    // O(log(n))
    void heapify_up(int i) {
        if (i == 0) {
            return;
        }
        int parent = (i - 1) / 2;
        if (this->min_heap[parent]->val > this->min_heap[i]->val) {
            this->swap(parent, i);
            heapify_up(parent);
        }
        
        return;
    }
    
    // O(log(n)), if the parent is larger than one of the children, then the parent goes down
    void heapify_down(int i) {
        int l = 2 * i + 1;
        int r = 2 * i + 2;
        if (l >= this->min_heap.size()) return;
        if (r >= this->min_heap.size()) {
            if (this->min_heap[l]->val < this->min_heap[i]->val) this->swap(i, l);
            return;
        }
        
        int min = (this->min_heap[l]->val < this->min_heap[r]->val) ? l : r;
        if (this->min_heap[min]->val < this->min_heap[i]->val) {
            this->swap(i, min);
            heapify_down(min);
        }
        
        return;
    }
    
    void swap(int i, int j) {
        ListNode* tmp = this->min_heap[i];
        this->min_heap[i] = this->min_heap[j];
        this->min_heap[j] = tmp;
    }
};

class Solution1 {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if (lists.empty()) {
            return nullptr;
        }
        if (lists.size() == 1) {
            return lists[0];
        }
        
        ListNode dummy(0);
        ListNode* cur = &dummy;
        // auto comp = [](ListNode* a, ListNode* b) {return a->val > b->val;};
        // min heap
        // std::priority_queue<ListNode*, vector<ListNode*>, decltype(comp)> q(comp);
        MinHeap q;
        for (auto head: lists) {
            if (head) q.push(head);
        }
        
        while (!q.empty()) {
            cur->next = q.top();
            cur = cur->next;
            q.pop();
            if (cur->next) q.push(cur->next);
        }
        
        return dummy.next;
    }
};

class Solution2 {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if (lists.empty()) {
            return nullptr;
        }
        if (lists.size() == 1) {
            return lists[0];
        }
        
        return merge_lists(lists, 0, lists.size() - 1);
    }
    
    ListNode* merge_lists(vector<ListNode*>& lists, int l, int r) {
        if (l > r) {
            return nullptr;
        }
        if (l == r) {
            return lists[l];
        }
        int mid = (l + r) / 2;
        ListNode* merged1 = merge_lists(lists, l, mid);
        ListNode* merged2 = merge_lists(lists, mid+1, r);
        return merge_two_lists(merged1, merged2);
    }
    
    ListNode* merge_two_lists(ListNode* l1, ListNode* l2) {
        if (!l1) return l2;
        if (!l2) return l1;
        
        ListNode dummy(0);
        ListNode* cur = &dummy;
        while (l1 && l2) {
            if (l1->val > l2->val) std::swap(l1, l2);
            cur->next = l1;
            cur =cur->next;
            l1 = l1->next;
        }
        
        if (l1) cur->next = l1;
        if (l2) cur->next = l2;
        return dummy.next;
    }
};