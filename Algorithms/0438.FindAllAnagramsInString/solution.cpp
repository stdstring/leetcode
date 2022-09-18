#include <algorithm>
#include <array>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::vector<int> findAnagrams(std::string const &s, std::string const &p) const
    {
        if (s.size() < p.size())
            return {};
        const std::array<int, AlphabetSize> pDescriptor(createDescriptor(p));
        std::array<int, AlphabetSize> diff(createDiff(s, p.size(), pDescriptor));
        std::vector<int> indices;
        if (checkDiff(diff))
            indices.push_back(0);
        for (size_t index = 1; index <= s.size() - p.size(); ++index)
        {
            ++diff[s[index - 1] - FirstChar];
            --diff[s[index + p.size() - 1] - FirstChar];
            if (checkDiff(diff))
                indices.push_back(static_cast<int>(index));
        }
        return indices;
    }

private:
    static constexpr int AlphabetSize = 26;
    static constexpr size_t FirstChar = 'a';

    std::array<int, AlphabetSize> createDescriptor(std::string const &source) const
    {
        std::array<int, AlphabetSize> descriptor{};
        descriptor.fill(0);
        for (char ch : source)
            ++descriptor[ch - FirstChar];
        return descriptor;
    }

    std::array<int, AlphabetSize> createDiff(std::string const &source, size_t size, std::array<int, AlphabetSize> const &descriptor) const
    {
        std::array<int, AlphabetSize> diff(descriptor);
        for (size_t index = 0; index < size; ++index)
            --diff[source[index] - FirstChar];
        return diff;
    }

    bool checkDiff(std::array<int, AlphabetSize> const &diff) const
    {
        return std::all_of(diff.cbegin(), diff.cend(), [](int letterDiff) { return letterDiff == 0; });
    }
};

}

namespace FindAllAnagramsInStringTask
{

TEST(FindAllAnagramsInStringTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<int>({0, 6}), solution.findAnagrams("cbaebabacd", "abc"));
    ASSERT_EQ(std::vector<int>({0, 1, 2}), solution.findAnagrams("abab", "ab"));
}

}