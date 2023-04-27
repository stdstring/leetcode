#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maxConsecutive(int bottom, int top, std::vector<int> const &special) const
    {
        std::vector<int> sortedSpecial(special);
        std::sort(sortedSpecial.begin(), sortedSpecial.end());
        int result = std::max(sortedSpecial.front() - bottom, top - sortedSpecial.back());
        for (size_t index = 1; index < sortedSpecial.size(); ++index)
            result = std::max(result, sortedSpecial[index] - sortedSpecial[index - 1] - 1);
        return result;
    }
};

}

namespace MaxConsecFloorsWithoutSpecialFloorsTask
{

TEST(MaxConsecFloorsWithoutSpecialFloorsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.maxConsecutive(2, 9, {4, 6}));
    ASSERT_EQ(0, solution.maxConsecutive(6, 8, {7, 6, 8}));
}

}