#include <string>
#include <unordered_map>
using namespace std;

// uses hashmap to store the prefixes and their accumulated values
// T(insertion): O(l) ~ O(l^2), if the length is too long, the prefixes will be too much to insert into hashmap,
// this might be time consuming
// T(query): O(1)
// T: O(nl) ~ O(nl^2)
// S: O(nl^2)
class MapSum {
public:
    MapSum(): m_(), prefix_sum_() {}
    
    void insert(string key, int val) {
        int delta = val;
        if (m_.count(key)) {
            delta -= m_[key];
        }

        m_[key] = val;
        
        for (int i = 1; i <= key.size(); ++i)
            prefix_sum_[key.substr(0, i)] += delta;
    }
    
    int sum(string prefix) {
        return prefix_sum_[prefix];
    }

private:
    unordered_map<string, int> m_;
    unordered_map<string, int> prefix_sum_;
};

// uses Trie to store the prefixes and their accumulated values
// T(insertion): O(l), T(query): O(l)
// T: O(nl)
// S: O(nl)
class MapSum {
public:
    MapSum(): root_(new TrieNode()) {}
    
    void insert(string key, int val) {
        int delta = val;
        if (kv_.count(key)) delta -= kv_[key];
        kv_[key] = val;
        
        TrieNode* curr = root_;
        for (auto c: key) {
            if (!curr->children[c - 'a']) curr->children[c - 'a'] = new TrieNode(delta);
            else curr->children[c - 'a']->sum += delta;
            curr = curr->children[c - 'a'];
        }
    }
    
    int sum(string prefix) {
        TrieNode* curr = root_;
        for (auto c: prefix) {
            if (!curr->children[c - 'a']) return 0;
            curr = curr->children[c - 'a'];
        }
        
        return curr->sum;
    }

private:
    struct TrieNode {
        int sum;
        vector<TrieNode*> children;
        
        TrieNode(): sum(0), children(26, nullptr) {}
        TrieNode(int val): sum(val), children(26, nullptr) {}
        
        ~TrieNode() {
            for (auto child: children)
                if (!child) delete child;
        }
    };
    
    TrieNode* root_;
    unordered_map<string, int> kv_;
};

/**
 * Your MapSum object will be instantiated and called as such:
 * MapSum* obj = new MapSum();
 * obj->insert(key,val);
 * int param_2 = obj->sum(prefix);
 */