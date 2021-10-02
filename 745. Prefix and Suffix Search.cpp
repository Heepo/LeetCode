#include <vector>
#include <string>
using namespace std;

struct TrieNode {
    int index;
    bool is_end;
    vector<TrieNode*> children;
    
    TrieNode():index(-1), is_end(false), children(27, nullptr) {};
    ~TrieNode() {
        for (auto child: children) {
            if (child) delete child;
        }
    }
};

class Trie {
public:
    // equivalent to `root = new TrieNode();`
    Trie():root(new TrieNode()) {}
    
    void insert(string& word, int index) {
        root->index = index;
        TrieNode* cur = root;
        for (char c: word) {
            int child = c - 'a';
            if (!cur->children[child]) cur->children[child] = new TrieNode();
            cur = cur->children[child];
            // updates index
            cur->index = index;
        }
        cur->is_end = true;
    }
    
    int query(string& prefix) {
        TrieNode* cur = root;
        for (char c: prefix) {
            int child = c - 'a';
            if (!cur->children[child]) return -1;
            
            cur = cur->children[child];
        }
        
        return cur->index;
    }

private:
    TrieNode* root;
};

// T: O(nl^2) + O(ql), l is the word length, each word has to insert l times, and the string concatenation cost O(l). 
// S: O(nl^2)
class WordFilter {
public:
    WordFilter(vector<string>& words):trie_() {
        for (int i = 0; i < words.size(); ++i) {
            string word = words[i];
            // "{" is right after "z" in the Ascii table
            string suffix = "{" + word;
            trie_.insert(suffix, i);
            for (int j = word.size() - 1; j >= 0; --j) {
                suffix = word[j] + suffix;
                trie_.insert(suffix, i);
            }
        }
    }
    
    int f(string prefix, string suffix) {
        // T: O(l)
        string key = suffix + "{" + prefix;
        return trie_.query(key);
    }

private:
    Trie trie_;
};

/**
 * Your WordFilter object will be instantiated and called as such:
 * WordFilter* obj = new WordFilter(words);
 * int param_1 = obj->f(prefix,suffix);
 */