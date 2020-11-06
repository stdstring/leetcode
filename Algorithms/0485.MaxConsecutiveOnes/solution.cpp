#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int findMaxConsecutiveOnes(std::vector<int> const &nums) const
    {
        int maxConsecutiveOnes = 0;
        int currentConsecutiveOnes = 0;
        for (int num : nums)
        {
            if (num == 0)
            {
                maxConsecutiveOnes = std::max(currentConsecutiveOnes, maxConsecutiveOnes);
                currentConsecutiveOnes = 0;
            }
            else
                ++currentConsecutiveOnes;
        }
        maxConsecutiveOnes = std::max(currentConsecutiveOnes, maxConsecutiveOnes);
        return maxConsecutiveOnes;
    }
};

}

namespace MaxConsecutiveOnesTask
{

TEST(MaxConsecutiveOnesTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(3, solution.findMaxConsecutiveOnes({1, 1, 0, 1, 1, 1}));
}

}