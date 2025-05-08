#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> m;
        for (int i = 0; i < nums.size(); ++i) {
            int val = nums[i];
            auto it = m.find(target - val);
            if (it != m.end()) {
                return {it->second, i};
            }
            m[val] = i;
        }
        return {};
    }
};
