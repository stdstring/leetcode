#include <algorithm>
#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::string getSmallestString(std::string const &s, int k) const
    {
        constexpr char alphabetStart = 'a';
        constexpr int alphabetSize = 26;
        std::string result(s);
        for (size_t index = 0; (index < result.size()) && (k > 0); ++index)
        {
            const int stepsToStartForward = alphabetSize - (result[index] - alphabetStart);
            const int stepsToStartBackward = result[index] - alphabetStart;
            const int minStepsToStart = std::min(stepsToStartForward, stepsToStartBackward);
            if (minStepsToStart <= k)
            {
                result[index] = alphabetStart;
                k -= minStepsToStart;
            }
            else
            {
                result[index] = static_cast<char>(result[index] - k);
                k = 0;
            }
        }
        return result;
    }
};

}

namespace LexSmallestStrAfterOpsConstraintTask
{

TEST(LexSmallestStrAfterOpsConstraintTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ("aaaz", solution.getSmallestString("zbbz", 3));
    ASSERT_EQ("aawcd", solution.getSmallestString("xaxcd", 4));
    ASSERT_EQ("lol", solution.getSmallestString("lol", 0));
}

}