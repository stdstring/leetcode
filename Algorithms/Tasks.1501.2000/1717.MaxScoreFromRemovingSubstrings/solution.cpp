#include <algorithm>
#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maximumGain(std::string const& s, int x, int y) const
    {
        // x - for "ab", y - for "ba"
        int result = 0;
        int aCount = 0;
        int bCount = 0;
        for (const char ch : s)
        {
            switch (ch)
            {
            case 'a':
                if ((bCount > 0) && (y >= x))
                {
                    result += y;
                    --bCount;
                }
                else
                    ++aCount;
                break;
            case 'b':
                if ((aCount > 0) && (x >= y))
                {
                    result += x;
                    --aCount;
                }
                else
                    ++bCount;
                break;
            default:
                result += std::min(aCount, bCount) * std::min(x, y);
                aCount = 0;
                bCount = 0;
                break;
            }
        }
        result += std::min(aCount, bCount) * std::min(x, y);
        return result;
    }
};

}

namespace MaxScoreFromRemovingSubstringsTask
{

TEST(MaxScoreFromRemovingSubstringsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(19, solution.maximumGain("cdbcbbaaabab", 4, 5));
    ASSERT_EQ(20, solution.maximumGain("aabbaaxybbaabb", 5, 4));
}

TEST(MaxScoreFromRemovingSubstringsTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    const std::string bigSource("aabbabkbbbfvybssbtaobaaaabataaadabbbmakgabbaoapbbbbobaabvqhbbzbbkapabaavbbeghacabamdpaaqbqabbjbababmbakbaabajabasaabbwabrbbaabbafubayaazbbbaababbaaha");
    ASSERT_EQ(112374, solution.maximumGain(bigSource, 1926, 4320));
}

}