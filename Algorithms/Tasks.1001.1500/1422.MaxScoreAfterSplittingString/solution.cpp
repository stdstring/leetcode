#include <algorithm>
#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maxScore(std::string const &s) const
    {
        const size_t zeroCount = std::ranges::count(s, '0');
        size_t leftZeroCount = s.front() == '0' ? 1 : 0;
        size_t bestScore = 0;
        for (size_t index = 1; index < s.size(); ++index)
        {
            const size_t rightZeroCount = zeroCount - leftZeroCount;
            const size_t rightOnesCount = s.size() - index - rightZeroCount;
            bestScore = std::max(bestScore, leftZeroCount + rightOnesCount);
            leftZeroCount += (s[index] == '0' ? 1 : 0);
        }
        return static_cast<int>(bestScore);
    }
};

}

namespace MaxScoreAfterSplittingStringTask
{

TEST(MaxScoreAfterSplittingStringTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(5, solution.maxScore("011101"));
    ASSERT_EQ(5, solution.maxScore("00111"));
    ASSERT_EQ(3, solution.maxScore("1111"));
}

}