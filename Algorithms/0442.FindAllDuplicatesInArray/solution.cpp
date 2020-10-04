#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::vector<int> findDuplicates(std::vector<int> &nums)
    {
        std::vector<int> result;
        for (int number : nums)
        {
            nums[abs(number) - 1] = -nums[abs(number) - 1];
        }
        for (int number : nums)
        {
            if (nums[abs(number) - 1] > 0)
            {
                result.push_back(abs(number));
                nums[abs(number) - 1] = -nums[abs(number) - 1];
            }
        }
        return result;
    }
};

}

namespace FindAllDuplicatesInArrayTask
{

TEST(FindAllDuplicatesInArrayTaskTests, Examples)
{
    Solution solution;
    std::vector<int> numbers({4, 3, 2, 7, 8, 2, 3, 1});
    ASSERT_EQ(std::vector<int>({3, 2}), solution.findDuplicates(numbers));
}

}