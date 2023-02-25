#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    bool isOneBitCharacter(std::vector<int> const &bits) const
    {
        int countOfOnes = 0;
        for (std::vector<int>::const_reverse_iterator iterator = bits.crbegin() + 1; iterator != bits.crend() && (*iterator) == 1; ++iterator)
            ++countOfOnes;
        return (countOfOnes % 2) == 0;
    }
};

}

namespace OneAndTwoBitCharactersTask
{

TEST(OneAndTwoBitCharactersTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(true, solution.isOneBitCharacter({1, 0, 0}));
    ASSERT_EQ(false, solution.isOneBitCharacter({1, 1, 1, 0}));
}

}