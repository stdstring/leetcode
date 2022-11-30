#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] bool uniqueOccurrences(std::vector<int> const &arr) const
    {
        std::unordered_map<int, size_t> numberCountMap;
        for (int number : arr)
            ++numberCountMap[number];
        std::unordered_set<size_t> countSet;
        for (auto [_, numberCount] : numberCountMap)
        {
            if (countSet.count(numberCount) > 0)
                return false;
            countSet.insert(numberCount);
        }
        return true;
    }
};

}

namespace UniqueNumberOfOccurrencesTask
{

TEST(UniqueNumberOfOccurrencesTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(true, solution.uniqueOccurrences({1, 2, 2, 1, 1, 3}));
    ASSERT_EQ(false, solution.uniqueOccurrences({1, 2}));
    ASSERT_EQ(true, solution.uniqueOccurrences({-3, 0, 1, -3, 1, 1, 1, -3, 10, 0}));
}

}