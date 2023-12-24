#include <algorithm>
#include <stdexcept>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minOperations(std::string const &s) const
    {
        // result must be 0 | 1 | (01)+ | (10)+
        size_t zeroStartOperations = 0;
        size_t oneStartOperations = 0;
        for (size_t index = 0; index < s.size(); ++index)
        {
            switch (index % 2)
            {
            case 0:
                zeroStartOperations += (s[index] == '0' ? 0 : 1);
                oneStartOperations += (s[index] == '1' ? 0 : 1);
                break;
            case 1:
                zeroStartOperations += (s[index] == '1' ? 0 : 1);
                oneStartOperations += (s[index] == '0' ? 0 : 1);
                break;
            default:
                throw std::logic_error("unexpected control flow");
            }
        }
        return static_cast<int>(std::min(zeroStartOperations, oneStartOperations));
    }
};

}

namespace MinChangesToMakeAlternatingBinStringTask
{

TEST(MinChangesToMakeAlternatingBinStringTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(1, solution.minOperations("0100"));
    ASSERT_EQ(0, solution.minOperations("10"));
    ASSERT_EQ(2, solution.minOperations("1111"));
}

TEST(MinChangesToMakeAlternatingBinStringTaskTests, CustomExamples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.minOperations("111101"));
    ASSERT_EQ(4, solution.minOperations("10111101"));
}

TEST(MinChangesToMakeAlternatingBinStringTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.minOperations("110010"));
}

}