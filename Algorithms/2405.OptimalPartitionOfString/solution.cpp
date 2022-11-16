#include <array>
#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int partitionString(std::string const &s) const
    {
        constexpr size_t alphabetSize = 26;
        constexpr size_t alphabetStart = 'a';
        std::array<bool, alphabetSize> letterData{};
        letterData.fill(false);
        size_t substringCount = 1;
        for (const char ch : s)
        {
            if (letterData[ch - alphabetStart])
            {
                letterData.fill(false);
                ++substringCount;
            }
            letterData[ch - alphabetStart] = true;
        }
        return static_cast<int>(substringCount);
    }
};

}

namespace OptimalPartitionOfStringTask
{

TEST(OptimalPartitionOfStringTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(4, solution.partitionString("abacaba"));
    ASSERT_EQ(6, solution.partitionString("ssssss"));
}

}