#include <algorithm>
#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int largestVariance(std::string const &s) const
    {
        int bestVariance = 0;
        for (size_t ch1 = 0; ch1 < AlphabetSize - 1; ++ch1)
        {
            for (size_t ch2 = ch1 + 1; ch2 < AlphabetSize; ++ch2)
                bestVariance = std::max(bestVariance, calcLargestVarianceImpl(s, ch1, ch2));
        }
        return bestVariance;
    }

private:
    static constexpr size_t AlphabetStart = 'a';
    static constexpr size_t AlphabetSize = 26;

    [[nodiscard]] int calcLargestVarianceImpl(std::string const &s, size_t ch1, size_t ch2) const
    {
        // Kadane's Algorithm
        bool hasTotalCh1 = false;
        bool hasTotalCh2 = false;
        int totalMax1 = INT_MIN;
        int currentMax1 = 0;
        bool hasCurrentCh2 = false;
        int totalMax2 = INT_MIN;
        int currentMax2 = 0;
        bool hasCurrentCh1 = false;
        for (const char ch : s)
        {
            const size_t current = ch - AlphabetStart;
            if (current == ch1)
                processChar(hasTotalCh1, totalMax1, currentMax1, hasCurrentCh1, hasTotalCh2, totalMax2, currentMax2, hasCurrentCh2);
            if (current == ch2)
                processChar(hasTotalCh2, totalMax2, currentMax2, hasCurrentCh2, hasTotalCh1, totalMax1, currentMax1, hasCurrentCh1); // NOLINT(readability-suspicious-call-argument)
        }
        return std::max(totalMax1, totalMax2);
    }

    void processChar(bool &hasTotalCh1,
                     int &totalMax1,
                     int &currentMax1,
                     bool &hasCurrentCh1,
                     bool const &hasTotalCh2,
                     int &totalMax2,
                     int &currentMax2,
                     bool const &hasCurrentCh2) const
    {
        hasTotalCh1 = true;
        ++currentMax1;
        if (!hasTotalCh2)
            return;
        totalMax1 = std::max(totalMax1, currentMax1 - (hasCurrentCh2 ? 0 : 1));
        hasCurrentCh1 = true;
        --currentMax2;
        if (currentMax2 < 0)
        {
            currentMax2 = 0;
            hasCurrentCh1 = false;
            return;
        }
        totalMax2 = std::max(totalMax2, currentMax2 - (hasCurrentCh1 ? 0 : 1));
    }
};

}

namespace SubstringWithLargestVarianceTask
{

TEST(SubstringWithLargestVarianceTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.largestVariance("aababbb"));
    ASSERT_EQ(0, solution.largestVariance("abcde"));
}

TEST(SubstringWithLargestVarianceTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(1, solution.largestVariance("bbc"));
    ASSERT_EQ(1, solution.largestVariance("ababab"));
}

}