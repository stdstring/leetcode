class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        if (nums.size() == 0)
            return 0;
        int length = 0;
        int shift = 0;
        for (int index = 0; index < nums.size(); ++index)
        {
            if (nums[index] == val)
            {
                ++shift;
            }
            else
            {
                ++length;
                nums[index - shift] = nums[index];
            }
        }
        return length;
    }
};