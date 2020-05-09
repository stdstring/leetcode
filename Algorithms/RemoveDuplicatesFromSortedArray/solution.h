class Solution {
public:
    int removeDuplicates(std::vector<int>& nums) {
        if (nums.size() == 0)
            return 0;
        int length = 1;
        int current = nums[0];
        int shift = 0;
        for (int index = 1; index < nums.size(); ++index)
        {
            if (current == nums[index])
            {
                ++shift;
            }
            else
            {
                ++length;
                current = nums[index];
                nums[index - shift] = current;
            }
        }
        return length;
    }
};