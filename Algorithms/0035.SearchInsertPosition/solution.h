class Solution
{
public:
    int searchInsert(std::vector<int> const &nums, int target)
    {
        if (nums.size() == 0)
            return 0;
        if (target <= nums[0])
            return 0;
        if (target == nums.back())
            return nums.size() - 1;
        if (target > nums.back())
            return nums.size();
        int left = 0;
        int right = nums.size() - 1;
        while (right - left > 1)
        {
            int middle = (right + left) / 2;
            if (nums[middle] == target)
                return middle;
            else if (nums[middle] < target)
                left = middle;
            else if (nums[middle] > target)
                right = middle;
        }
        return right;
    }
};