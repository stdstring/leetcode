class Solution
{
public:
    void moveZeroes(std::vector<int>& nums)
    {
        int zeroCount = 0;
        for (int index = 0; index < nums.size(); ++index)
        {
            if (nums[index] == 0)
                ++zeroCount;
            else
                nums[index - zeroCount] = nums[index];
        }
        if (zeroCount == nums.size())
            return;
        for (int index = nums.size() - zeroCount; index < nums.size(); ++index)
        {
            nums[index] = 0;
        }
    }
};