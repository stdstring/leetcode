#include <algorithm>
#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] bool makeStringsEqual(std::string const &s, std::string const &target) const
    {
        // s[i] = 0, s[j] = 0 -> s[i] = (s[i] OR s[j]) = 0, s[j] = (s[i] XOR s[j]) = 0
        // s[i] = 0, s[j] = 1 -> s[i] = (s[i] OR s[j]) = 1, s[j] = (s[i] XOR s[j]) = 1
        // s[i] = 1, s[j] = 0 -> s[i] = (s[i] OR s[j]) = 1, s[j] = (s[i] XOR s[j]) = 1
        // s[i] = 1, s[j] = 1 -> s[i] = (s[i] OR s[j]) = 1, s[j] = (s[i] XOR s[j]) = 0
        const size_t sourceOnes = std::ranges::count(s, '1');
        const size_t targetOnes = std::ranges::count(target, '1');
        return (sourceOnes == targetOnes) || ((sourceOnes > 0) && (targetOnes > 0));
    }
};

}

namespace ApplyBitwiseOpsMakeStringsEqualTask
{

TEST(ApplyBitwiseOpsMakeStringsEqualTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(true, solution.makeStringsEqual("1010", "0110"));
    ASSERT_EQ(false, solution.makeStringsEqual("11", "00"));
}

TEST(ApplyBitwiseOpsMakeStringsEqualTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(true, solution.makeStringsEqual("001000", "000100"));
}

}