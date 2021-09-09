#include <set>
#include <unordered_map>
using namespace std;

// T: get & put O(logn) because of insert & erase operations of bst
class LFUCache1 {
public:
    LFUCache1(int capacity) {
        capacity_ = capacity;
        tick_ = 0;
    }
    
    int get(int key) {
        auto it = m_.find(key);
        if (it == m_.end()) return -1;
        
        // found key
        touch(it->second);
        return it->second.value;
    }
    
    void put(int key, int value) {
        if (capacity_ == 0) return;
        auto it = m_.find(key);
        if (it != m_.end()) {
            it->second.value = value;
            touch(it->second);
            // m_[key] = it->second;
            return;
        }
        
        // Not found.
        if (cache_.size() == capacity_) {
            // erase the first node which has the smallest freq
            auto node = cache_.cbegin();
            // don't forget to erase the node from the map
            m_.erase(node->key);
            cache_.erase(*node); 
        }
        
        // Now the cache has enough space
        Node node{key, value, 1, ++tick_};
        cache_.insert(node);
        m_[key] = node;
    }

private:
    int capacity_;
    int tick_;
    struct Node {
        int key;
        int value;
        int freq;
        int tick;
        
        bool operator<(const Node& node) const {
            if (freq < node.freq) return true;
            if (freq == node.freq) return tick < node.tick;
            
            return false;
        }
    };
    // hash table
    unordered_map<int, Node> m_;
    // balanced search tree(red-black tree), insert & evict both in O(logn) time
    set<Node> cache_;
    
    // changes the status and re-balancing
    void touch(Node& node) {
        cache_.erase(node);
        node.freq++;
        node.tick = ++tick_;
        cache_.insert(node);
    }
};

// T: get & put O(1) using doubly linked list
class LFUCache2 {
public:
    LFUCache2(int capacity) {
        capacity_ = capacity;
        min_freq_ = 0;
    }
    
    int get(int key) {
        if (capacity_ == 0) return -1;
        auto it = m_.find(key);
        if (it == m_.end()) return -1;
        
        // found key
        touch(it->second);
        return it->second.value;
    }
    
    void put(int key, int value) {
        if (capacity_ == 0) return;
        
        auto it = m_.find(key);
        if (it != m_.end()) {
            it->second.value = value;
            touch(it->second);
            return;
        }
        
        // New key
        // ensures there is enough space
        if (m_.size() == capacity_) {
            m_.erase(l_[min_freq_].back());
            
            l_[min_freq_].pop_back();
            if (l_[min_freq_].empty()) l_.erase(min_freq_);
        }
        min_freq_ = 1;
        
        // insert the new key
        l_[min_freq_].push_front(key);
        // uses 1 not min_freq_ will report memory error
        m_[key] = {key, value, min_freq_, l_[min_freq_].begin()};
        return;
    }

private:
    int capacity_;
    int min_freq_;
    struct CacheNode {
        int key;
        int value;
        int freq;
        // pointer to the position in the same freq node list
        list<int>::iterator it;
    };
    // freq -> same freq keys
    unordered_map<int, list<int>> l_;
    // key -> CacheNode including the value, freq and the position in the same freq key list(stored in l_)
    unordered_map<int, CacheNode> m_;
    
    // nodes are registered before entering into touch
    void touch(CacheNode& node) {
        int pre_freq = node.freq;
        node.freq++;
        
        // removes from the old freq list
        l_[pre_freq].erase(node.it);
        // only when pre_freq == min_freq, the list needs to be deleted
        if (l_[pre_freq].empty() && pre_freq == min_freq_) {
            l_.erase(pre_freq);
            min_freq_++;
        }
        
        // inserts to new freq list
        l_[node.freq].push_front(node.key);
        
        // updates the key cachenode map
        m_[node.key].it = l_[node.freq].begin();
    }
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */