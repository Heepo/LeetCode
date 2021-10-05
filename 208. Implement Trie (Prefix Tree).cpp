#include <vector>
#include <string>
using namespace std;

class Trie {
public:
    Trie(): root_(new TrieNode()) {}
    
    void insert(string word) {
        TrieNode* curr = root_;
        for (char c: word) {
            if (!curr->children[c - 'a']) curr->children[c - 'a'] = new TrieNode();
            curr = curr->children[c - 'a'];
        }
        curr->is_end = true;
    }
    
    bool search(string word) {
        TrieNode* node = find_(word);
        return node && node->is_end;
    }
    
    bool startsWith(string prefix) {
        return find_(prefix) != nullptr;
    }

private:
    struct TrieNode {
        bool is_end;
        vector<TrieNode*> children;
        
        TrieNode(): is_end(false), children(vector<TrieNode*>(26, nullptr)) {}
        ~TrieNode() {
            for (auto child: children) {
                if (child) delete child;
            }
        }
    };
    
    TrieNode* root_;
    
    TrieNode* find_(string& word) {
        TrieNode* node = root_;
        for (char c: word) {
            node = node->children[c - 'a'];
            if (!node) return nullptr;
        }
        
        return node;
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */