// Scans once to record the last index of appearance for each character using an array.
// Scans again to extend the boundary of partitions to the maximum last index of characters that have appeared.
// Once the current index meets the boundary, a partition is formed.
// T: O(n)
// S: O(n)
class Solution {
public:
    vector<int> partitionLabels(string s) {
        vector<int> res;
        if (s.empty()) return res;
        
        vector<int> char_to_last_index(26, 0);
        for (int i = 0; i < s.size(); ++i) {
            char_to_last_index[s[i] - 'a'] = i;
        }

        int boundary = 0;
        int size = 0;
        for (int i = 0; i < s.size(); ++i) {
            size += 1;
            if (char_to_last_index[s[i] - 'a'] > boundary) boundary = char_to_last_index[s[i] - 'a'];
            if (i == boundary) {
                res.emplace_back(size);
                size = 0;
            }
        }

        return res;
    }
};

// from collections import defaultdict
# Uses a hashtable to scan the input once, storing the frequency of each character.
# Scans again to record each character's frequency up to the current index. If all frequencies reach their maximum(total remaining count decreases to 0),
# then this index marks a partition boundary.
// T: O(n)
// S: O(n)
// class Solution:
//     def partitionLabels(self, s: str) -> List[int]:
//         char_to_freq = defaultdict(int)
//         for char in s:
//             char_to_freq[char] += 1
        
//         remain_count = 0
//         partition_keys = set()
//         res = []
//         size = 0
//         for char in s:
//             size += 1
//             if char not in partition_keys:
//                 partition_keys.add(char)
//                 remain_count += char_to_freq[char]
//             remain_count -= 1
            
//             if remain_count == 0:
//                 res.append(size)
//                 size = 0
            
//         return res