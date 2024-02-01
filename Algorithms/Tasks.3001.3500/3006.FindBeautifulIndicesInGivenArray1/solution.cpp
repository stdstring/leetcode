#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> beautifulIndices(std::string const &s, std::string const &a, std::string const &b, int k) const
    {
        if ((s.size() < a.size()) || (s.size() < b.size()))
            return {};
        std::vector<int> aIndices;
        std::vector<int> bIndices;
        for (size_t index = 0; (index <= s.size() - a.size()) || (index <= s.size() - b.size()); ++index)
        {
            if ((index <= s.size() - a.size()) && (s.compare(index, a.size(), a) == 0))
                aIndices.emplace_back(static_cast<int>(index));
            if ((index <= s.size() - b.size()) && (s.compare(index, b.size(), b) == 0))
                bIndices.emplace_back(static_cast<int>(index));
        }
        std::vector<int> result;
        for (size_t aIndex = 0, bIndex = 0; aIndex < aIndices.size(); ++aIndex)
        {
            const int sIndex = aIndices[aIndex];
            while ((bIndex < bIndices.size()) && (bIndices[bIndex] < sIndex) && (std::abs(sIndex - bIndices[bIndex]) > k))
                ++bIndex;
            if (bIndex == bIndices.size())
                break;
            if (std::abs(sIndex - bIndices[bIndex]) <= k)
                result.emplace_back(sIndex);
        }
        return result;
    }
};

}

namespace FindBeautifulIndicesInGivenArray1Task
{

TEST(FindBeautifulIndicesInGivenArray1TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({16, 33}), solution.beautifulIndices("isawsquirrelnearmysquirrelhouseohmy", "my", "squirrel", 15));
    ASSERT_EQ(std::vector<int>({0}), solution.beautifulIndices("abcd", "a", "a", 4));
}

TEST(FindBeautifulIndicesInGivenArray1TaskTests, CustomExamples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>(), solution.beautifulIndices("i", "my", "squirrel", 1));
}

}