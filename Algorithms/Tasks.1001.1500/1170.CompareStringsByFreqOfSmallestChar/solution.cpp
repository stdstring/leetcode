#include <map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> numSmallerByFrequency(std::vector<std::string> const &queries, std::vector<std::string> const &words) const
    {
        std::map<size_t, size_t> frequencyMap;
        for (std::string const &word : words)
            ++frequencyMap[calcFValue(word)];
        size_t prevSum = 0;
        for (auto iterator = frequencyMap.rbegin(); iterator != frequencyMap.rend(); ++iterator)
        {
            iterator->second = prevSum + iterator->second;
            prevSum = iterator->second;
        }
        std::vector<int> results;
        for (std::string const &query : queries)
        {
            size_t queryFrequency = calcFValue(query);
            auto iterator = frequencyMap.upper_bound(queryFrequency);
            results.push_back(iterator == frequencyMap.cend() ? 0 : static_cast<int>(iterator->second));
        }
        return results;
    }

private:
    size_t calcFValue(std::string const &source) const
    {
        char smallestChar = source.front();
        size_t smallestCharCount = 0;
        for (const char ch : source)
        {
            if (ch < smallestChar)
            {
                smallestChar = ch;
                smallestCharCount = 0;
            }
            if (ch == smallestChar)
                ++smallestCharCount;
        }
        return smallestCharCount;
    }
};

}

namespace CompareStringsByFreqOfSmallestCharTask
{

TEST(CompareStringsByFreqOfSmallestCharTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector({1}), solution.numSmallerByFrequency({"cbd"}, {"zaaaz"}));
    ASSERT_EQ(std::vector({1, 2}), solution.numSmallerByFrequency({"bbb", "cc"}, {"a", "aa", "aaa", "aaaa"}));
}

}