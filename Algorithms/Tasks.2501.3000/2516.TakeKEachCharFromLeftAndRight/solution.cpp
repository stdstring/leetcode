#include <algorithm>
#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int takeCharacters(std::string const &s, int k) const
    {
        if (k == 0)
            return 0;
        constexpr size_t letterCount = 3;
        constexpr char alphabetStart = 'a';
        std::vector<int> charFreq(letterCount, 0);
        for (const char ch : s)
            ++charFreq[ch - alphabetStart];
        if (std::ranges::any_of(charFreq, [k](int count) { return count < k; }))
            return -1;
        size_t usedTime = s.size();
        for (size_t left = 0, right = 0; right < s.size(); ++right)
        {
            --charFreq[s[right] - alphabetStart];
            while (std::ranges::any_of(charFreq, [k](int count) { return count < k; }))
            {
                ++charFreq[s[left] - alphabetStart];
                ++left;
            }
            usedTime = std::min(usedTime, s.size() - (right - left + 1));
        }
        return static_cast<int>(usedTime);
    }
};

}

namespace TakeKEachCharFromLeftAndRightTask
{

TEST(TakeKEachCharFromLeftAndRightTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(8, solution.takeCharacters("aabaaaacaabc", 2));
    ASSERT_EQ(-1, solution.takeCharacters("a", 1));
}

TEST(TakeKEachCharFromLeftAndRightTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(0, solution.takeCharacters("a", 0));
    ASSERT_EQ(3, solution.takeCharacters("abc", 1));
    ASSERT_EQ(3, solution.takeCharacters("acba", 1));
}

}