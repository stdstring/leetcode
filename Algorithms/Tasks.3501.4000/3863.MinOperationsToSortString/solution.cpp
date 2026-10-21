#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minOperations(std::string const &s) const
    {
        bool isSorted = true;
        char minChar = s.front();
        size_t minCharCount = 1;
        char maxChar = s.front();
        size_t maxCharCount = 1;
        for (size_t index = 1; index < s.size(); ++index)
        {
            const char current = s[index];
            isSorted &= (s[index - 1] <= current);
            if (minChar == current)
                ++minCharCount;
            if (current < minChar)
            {
                minChar = current;
                minCharCount = 1;
            }
            if (maxChar == current)
                ++maxCharCount;
            if (current > maxChar)
            {
                maxChar = current;
                maxCharCount = 1;
            }
        }
        // already sorted => return 0
        if (isSorted)
            return 0;
        // length is 2 => return -1
        if (s.size() == 2)
            return -1;
        // (smallest character is at first) or (largest character is at last) => return 1
        if ((s.front() == minChar) || (s.back() == maxChar))
            return 1;
        // (one and only largest character at first) and (one and only smallest character at last) => return 3
        if ((minCharCount == 1) && (maxCharCount == 1) && (s.front() == maxChar) && (s.back() == minChar))
            return 3;
        // else => return 2
        return 2;
    }
};

}

namespace MinOperationsToSortStringTask
{

TEST(MinOperationsToSortStringTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(1, solution.minOperations("dog"));
    ASSERT_EQ(2, solution.minOperations("card"));
    ASSERT_EQ(-1, solution.minOperations("gf"));
}

}