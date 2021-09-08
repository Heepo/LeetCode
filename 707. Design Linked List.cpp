class MyLinkedList {
private:
    struct Node {
        int val;
        Node* next;
        Node* prev;
    };
    Node* head;
    Node* tail;
    int size;
public:
    /** Initialize your data structure here. */
    MyLinkedList() {
        head = nullptr;
        tail = nullptr;
        size = 0;
    }
    
    /** Get the value of the index-th node in the linked list. If the index is invalid, return -1. */
    int get(int index) {
        if (index < 0 || head == nullptr) {
            return -1;
        }
        if (index == 0) {
            return head->val;
        }
        
        Node* cur = head;
        for (int i = 0; i < index; i++) {
            cur = cur->next;
            if (cur == nullptr) {
                return -1;
            }
        }
        return cur->val;
    }
    
    /** Add a node of value val before the first element of the linked list. After the insertion, the new node will be the first node of the linked list. */
    void addAtHead(int val) {
        Node* node = new Node();
        node->val = val;
        node->next = head;
        node->prev = nullptr;
        if (head != nullptr) {
            head->prev = node;
        } else {
            tail = node;
        }
        head = node;
        size++;
    }
    
    /** Append a node of value val to the last element of the linked list. */
    void addAtTail(int val) {
        Node* node = new Node();
        node->val = val;
        node->next = nullptr;
        node->prev = tail;
        if (tail == nullptr) {
            tail = node;
            head = node;
        } else {
            tail->next = node;
            tail = node;
        }
        size++;
    }
    
    /** Add a node of value val before the index-th node in the linked list. If index equals to the length of linked list, the node will be appended to the end of linked list. If index is greater than the length, the node will not be inserted. */
    void addAtIndex(int index, int val) {
        if (index > size || index < 0) {
            return;
        }
        if (index == size) {
            addAtTail(val);
        } else if (index == 0) {
            addAtHead(val);
        } else {
            Node* node = new Node();
            node->val = val;
            Node* cur = head;
            for (int i = 0; i < index - 1; i++) {
                cur = cur->next;
            }
            node->next = cur->next;
            if (cur->next) {
                cur->next->prev = node;
            }
            cur->next = node;
            node->prev =cur;
            size++;
        }
        
    }
    
    /** Delete the index-th node in the linked list, if the index is valid. */
    void deleteAtIndex(int index) {
        if (index < 0 || index >= size) {
            return;
        }
        
        Node* cur = head;
        if (index == 0) {
            head = cur->next;
            delete cur;
            size--;
            return;
        }
        
        //std::cout << "size: " << size << std::endl;
        if (index == size - 1) {
            cur = tail;
            tail->prev->next = nullptr;
            tail = tail->prev;
            size--;
            delete cur;
            return;
        }
        //std::cout << cur->val << " ";
        for (int i = 0; i < index; i++) {
            cur = cur->next;
            //std::cout << cur->val << " ";
        }
        //std::cout << std::endl;
        if (cur->prev) {
            cur->prev->next = cur->next;
        }
        if (cur->next) {
            cur->next->prev = cur->prev;
        }
        cur->next = nullptr;
        cur->prev = nullptr;
        delete cur;
        size--;
        //std::cout << "deleted index" << index << std::endl;
    }
};

/**
 * Your MyLinkedList object will be instantiated and called as such:
 * MyLinkedList* obj = new MyLinkedList();
 * int param_1 = obj->get(index);
 * obj->addAtHead(val);
 * obj->addAtTail(val);
 * obj->addAtIndex(index,val);
 * obj->deleteAtIndex(index);
 */