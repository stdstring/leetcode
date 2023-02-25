#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::vector<int> findDisappearedNumbers(std::vector<int> &nums)
    {
        for (size_t index = 0; index < nums.size(); ++index)
        {
            const int absValue = abs(nums[index]);
            if (nums[absValue - 1] > 0)
                nums[absValue - 1] = -nums[absValue - 1];
        }
        std::vector<int> dest;
        for (size_t number = 1; number <= nums.size(); ++number)
        {
            if (nums[number - 1] > 0)
                dest.push_back(static_cast<int>(number));
        }
        return dest;
    }
};

}

namespace FindAllNumbersDisappearedInArrayTask
{

TEST(FindAllNumbersDisappearedInArrayTaskTests, Examples)
{
    Solution solution;
    std::vector<int> source({4, 3, 2, 7, 8, 2, 3, 1});
    ASSERT_EQ(std::vector<int>({5, 6}), solution.findDisappearedNumbers(source));
}

}