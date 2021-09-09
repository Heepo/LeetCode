#include <string>
#include <list>
#include <unordered_set>
#include <unordered_map>
#include <iostream>
using namespace std;

class AllOne {
public:
    /** Initialize your data structure here. */
    AllOne() {
        
    }
    
    /** Inserts a new key <Key> with value 1. Or increments an existing key by 1. */
    void inc(string key) {
        auto m_it = key_count_keys_m.find(key);
        // the key has never existed
        if (m_it == key_count_keys_m.end()) {
            // creates new node in list
            if (count_keys_list.empty() || count_keys_list.front().count > 1)
                count_keys_list.push_front(Node({1, {key}}));
            else
                count_keys_list.front().keys.insert(key);
            key_count_keys_m[key] = count_keys_list.begin();
        } else {
            auto l_it = m_it->second;
            auto n_it = next(l_it);
            // creates new node in list
            if (n_it == count_keys_list.end() || n_it->count != (l_it->count + 1))
                // NOTE: the returned value is the inserted node, it should be the new n_it
                n_it = count_keys_list.insert(n_it, Node({l_it->count + 1, {}}));
            n_it->keys.insert(key);
            key_count_keys_m[key] = n_it;
            
            l_it->keys.erase(key);
            if (l_it->keys.empty()) count_keys_list.erase(l_it);
        }
    }
    
    /** Decrements an existing key by 1. If Key's value is 1, remove it from the data structure. */
    void dec(string key) {
        auto m_it = key_count_keys_m.find(key);
        if (m_it == key_count_keys_m.end()) return;
        
        auto l_it = m_it->second;
        if (l_it->count > 1) {
            // creates a new node
            if (l_it == count_keys_list.begin() || (prev(l_it)->count + 1) != l_it->count)
                count_keys_list.insert(l_it, Node({l_it->count - 1, {key}}));
            else
                prev(l_it)->keys.insert(key);
            key_count_keys_m[key] = prev(l_it);
            
            l_it->keys.erase(key);
            if (l_it->keys.empty()) count_keys_list.erase(l_it);
        } else {
            l_it->keys.erase(key);
            if (l_it->keys.empty()) count_keys_list.erase(l_it);
            key_count_keys_m.erase(key);
        }
    }
    
    /** Returns one of the keys with maximal value. */
    string getMaxKey() {
        // print();
        return count_keys_list.empty() ? "" : *count_keys_list.back().keys.begin();
    }
    
    /** Returns one of the keys with Minimal value. */
    string getMinKey() {
        return count_keys_list.empty() ? "" : *count_keys_list.front().keys.begin();
    }
    
    void print() {
        for (auto m: key_count_keys_m) {
            std::cout << "m::key: " << m.first << " count: "<< m.second->count;
            for (auto key: m.second->keys) std::cout << " key: " << key << std::endl;
            
        }
        for (auto node: count_keys_list) {
            std::cout << "count_keys_list::count: " << node.count;
            for (auto key: node.keys) std::cout << " key: " << key << std::endl;
        }
        std::cout << std::endl;
    }

private:
    struct Node {
        int count;
        unordered_set<string> keys;
    };
    list<Node> count_keys_list;
    unordered_map<string, list<Node>::iterator> key_count_keys_m;
};

/**
 * Your AllOne object will be instantiated and called as such:
 * AllOne* obj = new AllOne();
 * obj->inc(key);
 * obj->dec(key);
 * string param_3 = obj->getMaxKey();
 * string param_4 = obj->getMinKey();
 */