#include <algorithm>
#include <iterator>
#include <map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] long long minCost(std::vector<int> const &basket1, std::vector<int> const &basket2) const
    {
        // prepare
        int globalMin = INT_MAX;
        std::map<int, int> unbalanced1;
        std::map<int, int> unbalanced2;
        for (int value : basket1)
        {
            ++unbalanced1[value];
            globalMin = std::min(globalMin, value);
        }
        for (int value : basket2)
        {
            globalMin = std::min(globalMin, value);
            auto iterator = unbalanced1.find(value);
            if (iterator == unbalanced1.end())
                ++unbalanced2[value];
            else
            {
                --iterator->second;
                if (iterator->second == 0)
                    unbalanced1.erase(iterator);
            }
        }
        // check
        if (!checkUnbalanced(unbalanced1) || !checkUnbalanced(unbalanced2))
            return -1;
        // count
        long long result = 0;
        while (!unbalanced1.empty() && !unbalanced2.empty())
            result += processUnbalanced(unbalanced1, unbalanced2, globalMin);
        return result;
    }

private:
    [[nodiscard]] bool checkUnbalanced(std::map<int, int> const &unbalanced) const
    {
        return std::ranges::all_of(unbalanced, [](std::pair<int, int> const& kvPair) { return (kvPair.second % 2) == 0; });
    }

    [[nodiscard]] long long processUnbalanced(std::map<int, int> &smallUnbalanced, std::map<int, int> &bigUnbalanced, int globalMin) const
    {
        if (bigUnbalanced.cbegin()->first < smallUnbalanced.cbegin()->first)
            return processUnbalanced(bigUnbalanced, smallUnbalanced, globalMin);
        auto smallIterator = smallUnbalanced.begin();
        auto bigIterator = std::prev(bigUnbalanced.end(), 1);
        int minCount = std::min(smallIterator->second, bigIterator->second);
        long long result = 1LL * calcMinChangeCost(smallIterator->first, globalMin) * minCount / 2;
        smallIterator->second -= minCount;
        bigIterator->second -= minCount;
        if (smallIterator->second == 0)
            smallUnbalanced.erase(smallIterator);
        if (bigIterator->second == 0)
            bigUnbalanced.erase(bigIterator);
        return result;
    }

    [[nodiscard]] int calcMinChangeCost(int localMin, int globalMin) const
    {
        // direct: a <--> b
        // indirect: a <--> minValue, minValue <--> b
        return std::min(localMin, 2 * globalMin);
    }
};

}

namespace RearrangingFruitsTask
{

TEST(RearrangingFruitsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(1, solution.minCost({4, 2, 2, 2}, {1, 4, 1, 2}));
    ASSERT_EQ(-1, solution.minCost({2, 3, 4, 1}, {3, 2, 5, 1}));
}

TEST(RearrangingFruitsTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(48, solution.minCost({84, 80, 43, 8, 80, 88, 43, 14, 100, 88}, {32, 32, 42, 68, 68, 100, 42, 84, 14, 8}));
}

}