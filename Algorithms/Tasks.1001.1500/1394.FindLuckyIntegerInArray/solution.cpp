#include <algorithm>
#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int findLucky(std::vector<int> const &arr) const
    {
        std::unordered_map<int, int> frequencyMap;
        for (int number : arr)
            ++frequencyMap[number];
        int luckyInteger = -1;
        for (auto const &[number, frequency] : frequencyMap)
        {
            if (number == frequency)
                luckyInteger = std::max(luckyInteger, number);
        }
        return luckyInteger;
    }
};

}

namespace FindLuckyIntegerInArrayTask
{

TEST(FindLuckyIntegerInArrayTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.findLucky({2, 2, 3, 4}));
    ASSERT_EQ(3, solution.findLucky({1, 2, 2, 3, 3, 3}));
    ASSERT_EQ(-1, solution.findLucky({2, 2, 2, 3, 3}));
}

}