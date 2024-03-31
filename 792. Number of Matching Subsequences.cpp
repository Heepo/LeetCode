// Scans 's' to map the characters to their occurrence indices using a nested vector.
// For each word, iterate through it, and for each character, perform a binary search for the lower bound
// of the previous character's matching index plus one in the current character's occurrence indices array.
// The lower bound means you can either find the first matching, just higher than it, or nothing.
// T: O(S) + O(W * L * log(S)), where S is the length of 's', W is the number of words, and L is the length of each word.
// S: O(S)
class Solution {
public:
    int numMatchingSubseq(string s, vector<string>& words) {
        if (s.empty() || words.empty()) return 0;

        vector<vector<int> > char_to_occurrence_indices(26);
        for (int i = 0; i < s.size(); ++i) {
            char_to_occurrence_indices[s[i] - 'a'].push_back(i);
        }

        int answer = 0;
        for (string& word: words) answer += is_match(word, char_to_occurrence_indices);

        return answer;
    }

    bool is_match(const string& word, const vector<vector<int> >& char_to_occurrence_indices) {
        int previous_matching_index = -1;
        for (char c: word) {
            const vector<int>& occurrence_indices = char_to_occurrence_indices[c - 'a'];
            const auto it = std::lower_bound(occurrence_indices.begin(), occurrence_indices.end(), previous_matching_index + 1);
            if (it == occurrence_indices.end()) return false;
            previous_matching_index = *it;
        }

        return true;
    }
};