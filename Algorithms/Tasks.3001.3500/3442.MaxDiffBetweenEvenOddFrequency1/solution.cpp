#include <algorithm>
#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maxDifference(std::string const &s) const
    {
        constexpr size_t alphabetStart = 'a';
        constexpr size_t alphabetSize = 26;
        std::vector<int> frequencies(alphabetSize, 0);
        for (char ch : s)
            ++frequencies[ch - alphabetStart];
        int maxOddFrequency = 0;
        int minEvenFrequency = static_cast<int>(s.size());
        for (int frequency : frequencies)
        {
            if (frequency == 0)
                continue;
            if ((frequency % 2) == 0)
                minEvenFrequency = std::min(minEvenFrequency, frequency);
            else
                maxOddFrequency = std::max(maxOddFrequency, frequency);
        }
        return maxOddFrequency - minEvenFrequency;
    }
};

}

namespace MaxDiffBetweenEvenOddFrequency1Task
{

TEST(MaxDiffBetweenEvenOddFrequency1TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.maxDifference("aaaaabbc"));
    ASSERT_EQ(1, solution.maxDifference("abcabcab"));
}

}