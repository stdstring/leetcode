#include <cstdint>
#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int numSub(std::string const &s) const
    {
        constexpr uint64_t modValue = 1000000007;
        uint64_t substringsCount = 0;
        size_t onesBlockStart = std::string::npos;
        for (size_t index = 0; index < s.size(); ++index)
        {
            if (s[index] == '0' && onesBlockStart != std::string::npos)
            {
                substringsCount = (substringsCount + calcSubstringCount(onesBlockStart, index - 1)) % modValue;
                onesBlockStart = std::string::npos;
            }
            if (s[index] == '1' && onesBlockStart == std::string::npos)
                onesBlockStart = index;
        }
        if (onesBlockStart != std::string::npos)
            substringsCount = (substringsCount + calcSubstringCount(onesBlockStart, s.size() - 1)) % modValue;
        return static_cast<int>(substringsCount);
    }

private:
    [[nodiscard]] uint64_t calcSubstringCount(size_t blockStart, size_t blockEnd) const
    {
        const size_t blockSize = blockEnd - blockStart + 1;
        return (1 + blockSize) * blockSize / 2;
    }
};

}

namespace NumberOfSubstringsWithOnly1Task
{

TEST(NumberOfSubstringsWithOnly1TaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(9, solution.numSub("0110111"));
    ASSERT_EQ(2, solution.numSub("101"));
    ASSERT_EQ(21, solution.numSub("111111"));
    ASSERT_EQ(0, solution.numSub("000"));
}

}