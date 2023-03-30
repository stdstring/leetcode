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
    [[nodiscard]] bool isScramble(std::string const &s1, std::string const &s2) const
    {
        if (s1 == s2)
            return true;
        if (!isSame(createData(s1, 0, s1.size()), createData(s2, 0, s2.size())))
            return false;
        const size_t memoizationSize = (s1.size() + 1) * (s1.size() + 1);
        TMemoization memoization(memoizationSize, std::vector<std::optional<bool>>(memoizationSize, std::optional<bool>()));
        return isScramble(s1, 0, s2, 0, s1.size(), memoization);
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

namespace ScrambleStringTask
{

TEST(ScrambleStringTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(true, solution.isScramble("great", "rgeat"));
    ASSERT_EQ(false, solution.isScramble("abcde", "caebd"));
    ASSERT_EQ(true, solution.isScramble("a", "a"));
}

TEST(ScrambleStringTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(true, solution.isScramble("abcdbdacbdac", "bdacabcdbdac"));
    ASSERT_EQ(false, solution.isScramble("abcdd", "dbdac"));
}

}