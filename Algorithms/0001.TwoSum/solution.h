class Solution {
public:
    std::vector<int> twoSum(std::vector<int>& nums, int target) {
        std::unordered_map<int, int> indicesMap;
        for (int index = 0; index < nums.size(); ++index)
        {
            std::unordered_map<int, int>::const_iterator it = indicesMap.find(target - nums[index]);
            if (it != indicesMap.cend())
                return {it->second, index};
            if (indicesMap.find(nums[index]) == indicesMap.cend())
                indicesMap.emplace(nums[index], index);
        }
        return {};
    }
};