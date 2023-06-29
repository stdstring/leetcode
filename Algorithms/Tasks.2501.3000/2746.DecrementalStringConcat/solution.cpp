#include <algorithm>
#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minimizeConcatenatedLength(std::vector<std::string> const &words) const
    {
        constexpr size_t alphabetSize = 26;
        constexpr size_t alphabetStart = 'a';
        size_t bestLength = words.front().size();
        std::vector<std::vector<size_t>> dp(alphabetSize, std::vector<size_t>(alphabetSize, INT_MAX));
        dp[words.front().front() - alphabetStart][words.front().back() - alphabetStart] = words.front().size();
        for (size_t index = 1; index < words.size(); ++index)
        {
            std::vector<std::vector<size_t>> nextDp(alphabetSize, std::vector<size_t>(alphabetSize, INT_MAX));
            size_t currentBestLength = INT_MAX;
            const size_t wordStart = words[index].front() - alphabetStart;
            const size_t wordEnd = words[index].back() - alphabetStart;
            for (size_t startIndex = 0; startIndex < alphabetSize; ++startIndex)
            {
                for (size_t endIndex = 0; endIndex < alphabetSize; ++endIndex)
                {
                    if (dp[startIndex][endIndex] == INT_MAX)
                        continue;
                    nextDp[wordStart][endIndex] = std::min(nextDp[wordStart][endIndex],
                                                           dp[startIndex][endIndex] + words[index].size() - (wordEnd == startIndex ? 1 : 0));
                    currentBestLength = std::min(currentBestLength, nextDp[wordStart][endIndex]);
                    nextDp[startIndex][wordEnd] = std::min(nextDp[startIndex][wordEnd],
                                                           dp[startIndex][endIndex] + words[index].size() - (wordStart == endIndex ? 1 : 0));
                    currentBestLength = std::min(currentBestLength, nextDp[startIndex][wordEnd]);
                }
            }
            bestLength = currentBestLength;
            std::swap(dp, nextDp);
        }
        return static_cast<int>(bestLength);
    }
};

}

namespace DecrementalStringConcatTask
{

TEST(DecrementalStringConcatTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(4, solution.minimizeConcatenatedLength({"aa", "ab", "bc"}));
    ASSERT_EQ(2, solution.minimizeConcatenatedLength({"ab", "b"}));
    ASSERT_EQ(6, solution.minimizeConcatenatedLength({"aaa", "c", "aba"}));
}

}