#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    void sortColors(std::vector<int>& nums)
    {
        const int red = 0;
        const int white = 1;
        const int blue = 2;
        size_t redStart = nums.size();
        size_t whiteStart = nums.size();
        size_t blueStart = nums.size();
        for (size_t index = 0; index < nums.size(); ++index)
        {
            size_t insertIndex = 0;
            switch (nums[index])
            {
                case red:
                    insertIndex = processInsert(nums, whiteStart, processInsert(nums, blueStart, index));
                    if (redStart == nums.size())
                        redStart = insertIndex;
                    break;
                case white:
                    insertIndex = processInsert(nums, blueStart, index);
                    if (whiteStart == nums.size())
                        whiteStart = insertIndex;
                    break;
                case blue:
                    if (blueStart == nums.size())
                        blueStart = index;
                    break;
                default:
                    break;
            }
        }
    }

private:
    size_t processInsert(std::vector<int>& nums, size_t &regionStart, size_t index) const
    {
        const size_t insertIndex = regionStart == nums.size() ? index : regionStart;
        if (insertIndex == regionStart)
        {
            std::swap(nums[insertIndex], nums[index]);
            ++regionStart;
        }
        return insertIndex;
    }
};

}

namespace SortColorsTask
{

TEST(SortColorsTaskTests, Examples)
{
    Solution solution;
    std::vector<int> data({2, 0, 2, 1, 1, 0});
    ASSERT_NO_THROW(solution.sortColors(data));
    ASSERT_EQ(std::vector<int>({0, 0, 1, 1, 2, 2}), data);
}

}