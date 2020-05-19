class Solution {
public:
    int firstMissingPositive(std::vector<int> &nums) {
        int minValue = 0;
        int maxValue = 0;
        int count = 0;
        int currentIndex = 0;
        for (int index = 0; index < nums.size(); ++index)
        {
            if (nums[index] > 0)
            {
                ++count;
                nums[currentIndex++] = nums[index];
                minValue = (minValue == 0) || (nums[index] < minValue) ? nums[index] : minValue;
                maxValue = (maxValue == 0) || (nums[index] > maxValue) ? nums[index] : maxValue;
            }
        }
        if (minValue > 1)
            return 1;
        for (int index = 0; index < count; ++index)
        {
            int refIndex = abs(nums[index]) - minValue;
            if ((refIndex < count) && (nums[refIndex] > 0))
                nums[refIndex] = -nums[refIndex];
        }
        for (int index = 0; index < count; ++index)
        {
            if (nums[index] > 0)
                return minValue + index;
        }
        return maxValue + 1;
    }
};