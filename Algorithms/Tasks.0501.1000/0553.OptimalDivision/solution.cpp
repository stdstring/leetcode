#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::string optimalDivision(std::vector<int> const &nums) const
    {
        const bool hasDenominator = nums.size() > 1;
        std::string dest;
        // numerator
        dest.append(std::to_string(nums.front()));
        if (!hasDenominator)
            return dest;
        // denominator
        const bool hasComplexDenominator = nums.size() > 2;
        dest.push_back('/');
        if (hasComplexDenominator)
            dest.push_back('(');
        for (size_t index = 1; index < nums.size(); ++index)
        {
            if (index > 1)
                dest.push_back('/');
            dest.append(std::to_string(nums[index]));
        }
        if (hasComplexDenominator)
            dest.push_back(')');
        return dest;
    }
};

}

namespace OptimalDivisionTask
{

TEST(OptimalDivisionTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ("1000/(100/10/2)", solution.optimalDivision({1000, 100, 10, 2}));
    ASSERT_EQ("2/(3/4)", solution.optimalDivision({2, 3, 4}));
    ASSERT_EQ("2", solution.optimalDivision({2}));
}

TEST(OptimalDivisionTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ("3/2", solution.optimalDivision({3, 2}));
}

}