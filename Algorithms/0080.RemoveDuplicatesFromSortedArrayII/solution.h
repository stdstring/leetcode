class Solution {
public:
    int removeDuplicates(std::vector<int>& nums) {
        if (nums.size() == 0)
            return 0;
        int shift = 0;
        int length = 1;
        int value = nums[0];
        int count = 1;
        for (int index = 1; index < nums.size(); ++index)
        {
            if (nums[index] == value)
            {
                if (count < 2)
                {
                    ++count;
                    nums[index - shift] = value;
                    ++length;
                }
                else
                {
                    ++shift;
                }
            }
            else
            {
                value = nums[index];
                count = 1;
                nums[index - shift] = value;
                ++length;
            }
        }
        return length;
    }
};