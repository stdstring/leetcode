class Solution {
public:
    std::vector<int> twoSum(std::vector<int> const &nums, int target) {
        // create and sort vector of indices
        std::vector<int> indices;
        indices.reserve(nums.size());
        for (int index = 0; index < nums.size(); ++index)
        {
            indices.push_back(index);
        }
        std::sort(indices.begin(), indices.end(), [&nums](int left, int right){ return nums[left] < nums[right]; });
        // use two pointer approach
        int left = 0;
        int right = indices.size() - 1;
        while (left != right)
        {
            int value = nums[indices[left]] + nums[indices[right]];
            if (value == target)
            {
                return {indices[left], indices[right]};
            }
            else if (value < target)
            {
                ++left;
            }
            else if (value > target)
            {
                --right;
            }
        }
        return {};
    }
};