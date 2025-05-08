#include <string>
#include <unordered_set>

using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_set<char> chars;
        size_t maxlen = 0;
        size_t start = 0;
        size_t end = 0;
        while (end < s.length()) {
            char ch = s[end];
            if (chars.find(ch) == chars.end()) {
                chars.insert(ch);
                end++;
            } else {
                maxlen = max(end - start, maxlen);        
                chars.erase(s[start]);
                start++;
            }
        }
        return max(end - start, maxlen);
    }
};
