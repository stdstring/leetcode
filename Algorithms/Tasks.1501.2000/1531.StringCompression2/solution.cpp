#include <algorithm>
#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int getLengthOfOptimalCompression(std::string const &s, int k) const
    {
        std::vector<std::vector<size_t>> dp(s.size(), std::vector<size_t>(k + 1, INT_MAX));
        for (size_t startIndex = 0; startIndex < s.size(); ++startIndex)
        {
            for (int deleted = 0; deleted <= k; ++deleted)
            {
                const size_t currentLength = (startIndex > 0 ? dp[startIndex - 1][deleted] : (deleted == 0 ? 0 : INT_MAX));
                if (currentLength == INT_MAX)
                    continue;
                size_t charCount = 0;
                int currentDeleted = 0;
                for (size_t finishIndex = startIndex; finishIndex < s.size(); ++finishIndex)
                {
                    if (s[finishIndex] == s[startIndex])
                        ++charCount;
                    else
                        ++currentDeleted;
                    if ((deleted + currentDeleted) > k)
                        break;
                    dp[finishIndex][deleted + currentDeleted] = std::min(dp[finishIndex][deleted + currentDeleted], currentLength + calcSegmentSize(charCount));
                }
                if (deleted < k)
                    dp[startIndex][deleted + 1] = std::min(dp[startIndex][deleted + 1], currentLength);
            }
        }
        return static_cast<int>(*std::ranges::min_element(dp.back()));
    }

private:
    size_t calcSegmentSize(size_t charCount) const
    {
        if (charCount == 1)
            return 1;
        if (charCount < 10)
            return 1 + 1;
        if (charCount < 100)
            return 1 + 2;
        if (charCount < 1000)
            return 1 + 3;
        throw std::logic_error("Unsupported value of charCount");
    }
};

}

namespace StringCompression2Task
{

TEST(StringCompression2TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(4, solution.getLengthOfOptimalCompression("aaabcccd", 2));
    ASSERT_EQ(2, solution.getLengthOfOptimalCompression("aabbaa", 2));
    ASSERT_EQ(3, solution.getLengthOfOptimalCompression("aaaaaaaaaaa", 0));
}

TEST(StringCompression2TaskTests, CustomExamples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.getLengthOfOptimalCompression("aaaaaaaaaa", 1));
}

TEST(StringCompression2TaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(1, solution.getLengthOfOptimalCompression("abc", 2));
}

}