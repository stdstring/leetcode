#include <algorithm>
#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int numWays(std::string const &s) const
    {
        constexpr int64_t modValue = 1000000007;
        const size_t onesCount = std::count(s.cbegin(), s.cend(), '1');
        if (onesCount % 3 != 0)
            return 0;
        if (onesCount == 0)
            return static_cast<int>(((s.size() - 1) * (s.size() - 2)) / 2 % modValue);
        const size_t firstPortionEnd = findPortionEnd(s, 0, onesCount / 3);
        const size_t secondPortionStart = findPortionStart(s, firstPortionEnd + 1);
        const size_t secondPortionEnd = findPortionEnd(s, secondPortionStart, onesCount / 3);
        const size_t thirdPortionStart = findPortionStart(s, secondPortionEnd + 1);
        return static_cast<int>(((secondPortionStart - firstPortionEnd) * (thirdPortionStart - secondPortionEnd)) % modValue);
    }

private:
    [[nodiscard]] size_t findPortionStart(std::string const& source, size_t start) const
    {
        size_t index = start;
        for (; source[index] == '0'; ++index);
        return index;
    }

    [[nodiscard]] size_t findPortionEnd(std::string const &source, size_t start, size_t portionSize) const
    {
        size_t index = start;
        for (size_t portionCount = 0; portionCount < portionSize; ++index)
        {
            if (source[index] == '1')
                ++portionCount;
        }
        return index - 1;
    }
};

}

namespace NumberOfWaysToSplitStringTask
{

TEST(NumberOfWaysToSplitStringTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(4, solution.numWays("10101"));
    ASSERT_EQ(0, solution.numWays("1001"));
    ASSERT_EQ(3, solution.numWays("0000"));
}

}