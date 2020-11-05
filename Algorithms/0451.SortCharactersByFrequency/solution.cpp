#include <algorithm>
#include <array>
#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::string frequencySort(std::string const &s) const
    {
        constexpr size_t alphabetSize = 256;
        std::array<size_t, alphabetSize> charFrequency{};
        charFrequency.fill(0);
        for (char ch : s)
            ++charFrequency[ch];
        std::vector<size_t> charIndices;
        for (size_t index = 0; index < alphabetSize; ++index)
            charIndices.push_back(index);
        std::sort(charIndices.begin(), charIndices.end(), [&charFrequency](size_t left, size_t right){ return charFrequency[left] > charFrequency[right]; });
        std::string dest;
        for (size_t index = 0; (index < alphabetSize) && (charFrequency[charIndices[index]] > 0); ++index)
            dest.append(charFrequency[charIndices[index]], static_cast<char>(charIndices[index]));
        return dest;
    }
};

}

namespace SortCharactersByFrequencyTask
{

TEST(SortCharactersByFrequencyTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ("eert", solution.frequencySort("tree"));
    ASSERT_EQ("cccaaa", solution.frequencySort("cccaaa"));
    ASSERT_EQ("bbaA", solution.frequencySort("Aabb"));
}

}