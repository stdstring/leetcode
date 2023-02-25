#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int bagOfTokensScore(std::vector<int> const &tokens, int power) const
    {
        size_t score = 0;
        std::vector<int> sortedTokens(tokens);
        std::sort(sortedTokens.begin(), sortedTokens.end());
        if (sortedTokens.empty() || (power < sortedTokens.front()))
            return 0;
        size_t left = 0;
        size_t right = sortedTokens.size() - 1;
        while (right > left)
        {
            if (power >= sortedTokens[left])
            {
                power -= sortedTokens[left++];
                ++score;
            }
            else
            {
                power += sortedTokens[right--];
                --score;
            }
        }
        if (power >= sortedTokens[left])
            ++score;
        return static_cast<int>(score);
    }
};

}

namespace BagOfTokensTask
{

TEST(BagOfTokensTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(0, solution.bagOfTokensScore({100}, 0));
    ASSERT_EQ(1, solution.bagOfTokensScore({100, 200}, 150));
    ASSERT_EQ(2, solution.bagOfTokensScore({100, 200, 300, 400}, 200));
}

TEST(BagOfTokensTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(0, solution.bagOfTokensScore({}, 85));
    ASSERT_EQ(1, solution.bagOfTokensScore({81, 91, 31}, 73));
}

}