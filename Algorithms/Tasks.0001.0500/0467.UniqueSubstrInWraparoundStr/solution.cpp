#include <array>
#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int findSubstringInWraproundString(std::string const &p) const
    {
        std::array<size_t, AlphabetSize> knownSubstrings{};
        knownSubstrings.fill(0);
        size_t result = 0;
        size_t start = 0;
        for (size_t index = 1; index < p.size(); ++index)
        {
            const char expectedChar = static_cast<char>(AlphabetStart + (p[index - 1] + 1 -AlphabetStart) % AlphabetSize);
            if (p[index] != expectedChar)
            {
                result += calcUniqueSubstringCount(p, start, index - start, knownSubstrings);
                start = index;
            }
        }
        result += calcUniqueSubstringCount(p, start, p.size() - start, knownSubstrings);
        return static_cast<int>(result);
    }

private:
    static constexpr size_t AlphabetStart = 'a';
    static constexpr size_t AlphabetSize = 26;

    size_t calcUniqueSubstringCount(std::string const &source, size_t start, size_t count, std::array<size_t, AlphabetSize> &knownSubstrings) const
    {
        size_t substringCount = 0;
        for (size_t shift = 0; shift < count; ++shift)
        {
            const size_t maxSubstringSize = count - shift;
            if (knownSubstrings[source[start + shift] - AlphabetStart] >= maxSubstringSize)
                return substringCount;
            const size_t prevSubstringSize = knownSubstrings[source[start + shift] - AlphabetStart];
            substringCount += maxSubstringSize - prevSubstringSize;
            knownSubstrings[source[start + shift] - AlphabetStart] = maxSubstringSize;
        }
        return substringCount;
    }
};

}

namespace UniqueSubstrInWraparoundStrTask
{

TEST(UniqueSubstrInWraparoundStrTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(1, solution.findSubstringInWraproundString("a"));
    ASSERT_EQ(2, solution.findSubstringInWraproundString("cac"));
    ASSERT_EQ(6, solution.findSubstringInWraproundString("zab"));
}

}