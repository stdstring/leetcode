#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] bool canConvertString(std::string const &s, std::string const &t, int k) const
    {
        if (s.size() != t.size())
            return false;
        constexpr int alphabetSize = 26;
        std::vector<int> shiftData(alphabetSize, 0);
        for (size_t index = 0; index < s.size(); ++index)
        {
            if (s[index] != t[index])
            {
                int shift = t[index] - s[index] + (s[index] < t[index] ? 0 : alphabetSize);
                shift += alphabetSize * (shiftData[shift]++);
                if (shift > k)
                    return false;
            }
        }
        return true;
    }
};

}

namespace CanConvertStringInKMovesTask
{

TEST(CanConvertStringInKMovesTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(true, solution.canConvertString("input", "ouput", 9));
    ASSERT_EQ(false, solution.canConvertString("abc", "bcd", 10));
    ASSERT_EQ(true, solution.canConvertString("aab", "bbb", 27));
}

}