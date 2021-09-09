#include <list>
#include <unordered_set>
#include <unordered_map>
using namespace std;

class LRUCache {
public:
    LRUCache(int capacity) {
        capacity_ = capacity;
    }
    
    int get(int key) {
        auto it = m_.find(key);
        if (it == m_.end()) return -1;
        
        // found key
        // moves the key value pair into the beginning
        cache_.splice(cache_.begin(), cache_, it->second);
        return it->second->second;
    }
    
    void put(int key, int value) {
        auto it = m_.find(key);
        if (it != m_.end()) {
            it->second->second = value;
            cache_.splice(cache_.begin(), cache_, it->second);
            return;
        }
            
        // Not found. Ensures there is free capacity first
        if (cache_.size() == capacity_) {
            auto back = cache_.back();
            cache_.pop_back();
            m_.erase(back.first);
        }
        cache_.emplace_front(key, value);
        m_[key] = cache_.begin();
        return;
    }
    
private:
    int capacity_;
    list<pair<int, int>> cache_;
    unordered_map<int, list<pair<int, int>>::iterator> m_;
};
/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */