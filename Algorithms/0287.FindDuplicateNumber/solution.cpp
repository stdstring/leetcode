#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int findDuplicate(std::vector<int> const &nums) const
    {
        int duplicate = 0;
        const int n = static_cast<int>(nums.size()) - 1;
        for (int bit = 0, mask = 1 << bit; mask <= n; ++bit, mask = 1 << bit)
        {
            size_t baseCount = 0;
            size_t currentCount = 0;
            for (size_t index = 0; index < nums.size(); ++index)
            {
                int number = static_cast<int>(index) + 1;
                if ((number <= n) && ((number & mask) != 0))
                    ++baseCount;
                if ((nums[index] & mask) != 0)
                    ++currentCount;
            }
            if (currentCount > baseCount)
                duplicate |= mask;
        }
        return duplicate;
    }
};

}

namespace FindDuplicateNumberTask
{

TEST(FindDuplicateNumberTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(2, solution.findDuplicate({1, 3, 4, 2, 2}));
    ASSERT_EQ(3, solution.findDuplicate({3, 1, 3, 4, 2}));
}

}