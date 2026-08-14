#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maximumLengthSubstring(std::string const &s) const
    {
        constexpr size_t alphabetSize = 26;
        constexpr size_t alphabetStart = 'a';
        std::vector<size_t> letterData(alphabetSize, 0);
        size_t maxLength = 0;
        for (size_t start = 0, end = 0; end < s.size(); ++end)
        {
            const size_t current = s[end] - alphabetStart;
            ++letterData[current];
            for (; letterData[current] > 2; ++start)
                --letterData[s[start] - alphabetStart];
            maxLength = std::max(maxLength, end - start + 1);
        }
        return static_cast<int>(maxLength);
    }
};

}

namespace MaxLengthSubstrWith2OccurrencesTask
{

TEST(MaxLengthSubstrWith2OccurrencesTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(4, solution.maximumLengthSubstring("bcbbbcba"));
    ASSERT_EQ(2, solution.maximumLengthSubstring("aaaa"));
}

}