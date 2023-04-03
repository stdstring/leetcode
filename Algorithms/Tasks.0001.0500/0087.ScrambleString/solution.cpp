#include <array>
#include <optional>
#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] bool isScrambleViaEnumeration(std::string const &s1, std::string const &s2) const
    {
        if (s1 == s2)
            return true;
        if (!isSame(createData(s1, 0, s1.size()), createData(s2, 0, s2.size())))
            return false;
        const size_t memoizationSize = (s1.size() + 1) * (s1.size() + 1);
        TMemoization memoization(memoizationSize, std::vector<std::optional<bool>>(memoizationSize, std::optional<bool>()));
        return isScramble(s1, 0, s2, 0, s1.size(), memoization);
    }

    [[nodiscard]] bool isScrambleViaDp(std::string const &s1, std::string const &s2) const
    {
        const size_t size = s1.size();
        std::vector<std::vector<std::vector<bool>>> dp(size + 1, std::vector<std::vector<bool>>(size, std::vector<bool>(size, false)));
        for (size_t index1 = 0; index1 < size; ++index1)
        {
            for (size_t index2 = 0; index2 < size; ++index2)
                dp[1][index1][index2] = (s1[index1] == s2[index2]);
        }
        for (size_t portionSize = 2; portionSize <= size; ++portionSize)
        {
            for (size_t index1 = 0; index1 < size - portionSize + 1; ++index1)
            {
                for (size_t index2 = 0; index2 < size - portionSize + 1; ++index2)
                {
                    for (size_t splitSize = 1; splitSize < portionSize; ++splitSize)
                    {
                        std::vector<bool> const &dp1(dp[splitSize][index1]);
                        std::vector<bool> const &dp2(dp[portionSize - splitSize][index1 + splitSize]);
                        dp[portionSize][index1][index2] = dp[portionSize][index1][index2] || (dp1[index2] && dp2[index2 + splitSize]);
                        dp[portionSize][index1][index2] = dp[portionSize][index1][index2] || (dp1[index2 + portionSize - splitSize] && dp2[index2]);
                    }
                }
            }
        }
        return dp[size][0][0];
    }

private:
    static constexpr size_t AlphabetSize = 26;
    static constexpr size_t AlphabetStart = 'a';

    typedef std::vector<std::vector<std::optional<bool>>> TMemoization;

    [[nodiscard]] bool isSame(std::array<size_t, AlphabetSize> const &data1, std::array<size_t, AlphabetSize> const &data2) const
    {
        for (size_t index = 0; index < AlphabetSize; ++index)
        {
            if (data1[index] != data2[index])
                return false;
        }
        return true;
    }

    [[nodiscard]] std::array<size_t, AlphabetSize> createData(std::string const &s, size_t index, size_t size) const
    {
        std::array<size_t, AlphabetSize> data{};
        data.fill(0);
        for (size_t shift = 0; shift < size; ++shift)
            ++data[s[index + shift] - AlphabetStart];
        return data;
    }

    [[nodiscard]] bool isScramble(std::string const &s1,
                                  size_t index1,
                                  std::string const &s2,
                                  size_t index2,
                                  size_t size,
                                  TMemoization &memoization) const
    {
        if (size == 1)
            return s1[index1] == s2[index2];
        const size_t s1MemoizationIndex = index1 * (s1.size() + 1) + size;
        const size_t s2MemoizationIndex = index2 * (s2.size() + 1) + size;
        if (memoization[s1MemoizationIndex][s2MemoizationIndex].has_value())
            return memoization[s1MemoizationIndex][s2MemoizationIndex].value();
        std::array<size_t, AlphabetSize> prefix1Data{};
        prefix1Data.fill(0);
        std::array<size_t, AlphabetSize> prefix2Data{};
        prefix2Data.fill(0);
        std::array<size_t, AlphabetSize> suffix2Data{};
        suffix2Data.fill(0);
        for (size_t shift = 0; shift < size - 1; ++shift)
        {
            ++prefix1Data[s1[index1 + shift] - AlphabetStart];
            ++prefix2Data[s2[index2 + shift] - AlphabetStart];
            ++suffix2Data[s2[index2 + size - 1 - shift] - AlphabetStart];
            if (isSame(prefix1Data, prefix2Data) &&
                isScramble(s1, index1, s2, index2, shift + 1, memoization) &&
                isScramble(s1, index1 + shift + 1, s2, index2 + shift + 1, size - shift - 1, memoization))
            {
                memoization[s1MemoizationIndex][s2MemoizationIndex] = true;
                return true;
            }
            if (isSame(prefix1Data, suffix2Data) &&
                isScramble(s1, index1, s2, index2 + size - 1 - shift, shift + 1, memoization) &&
                isScramble(s1, index1 + shift + 1, s2, index2, size - shift - 1, memoization))
            {
                memoization[s1MemoizationIndex][s2MemoizationIndex] = true;
                return true;
            }
        }
        memoization[s1MemoizationIndex][s2MemoizationIndex] = false;
        return false;
    }
};

}

namespace
{

void checkIsScramble(std::string const &s1, std::string const &s2, bool expectedValue)
{
    constexpr Solution solution;
    ASSERT_EQ(expectedValue, solution.isScrambleViaEnumeration(s1, s2));
    ASSERT_EQ(expectedValue, solution.isScrambleViaDp(s1, s2));
}

}

namespace ScrambleStringTask
{

TEST(ScrambleStringTaskTests, Examples)
{
    checkIsScramble("great", "rgeat", true);
    checkIsScramble("abcde", "caebd", false);
    checkIsScramble("a", "a", true);
}

TEST(ScrambleStringTaskTests, FromWrongAnswers)
{
    checkIsScramble("abcdbdacbdac", "bdacabcdbdac", true);
    checkIsScramble("abcdd", "dbdac", false);
}

}