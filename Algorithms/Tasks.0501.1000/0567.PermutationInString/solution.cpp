#include <array>
#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    bool checkInclusion(std::string const &s1, std::string const &s2) const
    {
        if (s1.size() > s2.size())
            return false;
        const std::array<size_t, AlphabetSize> referenceMetric(createFreqMetric(s1, s1.size()));
        std::array<size_t, AlphabetSize> windowMetric(createFreqMetric(s2, s1.size()));
        if (compareFreqMetrics(referenceMetric, windowMetric))
            return true;
        for (size_t index = 0; index < s2.size() - s1.size(); ++index)
        {
            --windowMetric[s2[index] - AlphabetStart];
            ++windowMetric[s2[index + s1.size()] - AlphabetStart];
            if (compareFreqMetrics(referenceMetric, windowMetric))
                return true;
        }
        return false;
    }

private:
    constexpr static size_t AlphabetSize = 26;
    constexpr static size_t AlphabetStart = 'a';

    std::array<size_t, AlphabetSize> createFreqMetric(std::string const &source, size_t size) const
    {
        std::array<size_t, AlphabetSize> freqMetric{};
        freqMetric.fill(0);
        for (size_t index = 0; index < size; ++index)
            ++freqMetric[source[index] - AlphabetStart];
        return freqMetric;
    }

    bool compareFreqMetrics(std::array<size_t, AlphabetSize> const &freqMetric1, std::array<size_t, AlphabetSize> const &freqMetric2) const
    {
        return freqMetric1 == freqMetric2;
    }
};

}

namespace PermutationInStringTask
{

TEST(PermutationInStringTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(true, solution.checkInclusion("ab", "eidbaooo"));
    ASSERT_EQ(false, solution.checkInclusion("ab", "eidboaoo"));
}

TEST(PermutationInStringTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(true, solution.checkInclusion("adc", "dcda"));
    ASSERT_EQ(false, solution.checkInclusion("ab", "a"));
}

}