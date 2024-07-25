#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minimumLength(std::string const &s) const
    {
        // 6 -> 4 -> 2
        // 5 -> 3 -> 1
        constexpr size_t alphabetStart = 'a';
        constexpr size_t alphabetSize = 26;
        std::vector<size_t> letterData(alphabetSize, 0);
        for (const char ch : s)
            ++letterData[ch - alphabetStart];
        size_t result = 0;
        for (const size_t count : letterData)
            result += (count == 0) ? 0 : 2 - (count % 2);
        return static_cast<int>(result);
    }
};

}

namespace MinLengthOfStringAfterOperationsTask
{

TEST(MinLengthOfStringAfterOperationsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(5, solution.minimumLength("abaacbcbb"));
    ASSERT_EQ(2, solution.minimumLength("aa"));
}

}