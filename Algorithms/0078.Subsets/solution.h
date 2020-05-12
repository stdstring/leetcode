class Solution {
public:
    std::vector<std::vector<int>> subsets(std::vector<int> const &nums) {
        int subsetsCount = 1 << nums.size();
        std::vector<std::vector<int>> subsets;
        subsets.reserve(subsetsCount);
        subsets.push_back({});
        for (int mask = 1; mask < subsetsCount; ++mask)
        {
            subsets.push_back(createSubsetByMask(nums, mask));
        }
        return subsets;
    }

private:
    std::vector<int> createSubsetByMask(std::vector<int> const &nums, int mask)
    {
        std::vector<int> subset;
        subset.reserve(nums.size());
        for (int index = 0; index < nums.size(); ++index)
        {
            if ((mask & (1 << index)) > 0)
                subset.push_back(nums[index]);
        }
        return subset;
    }
};