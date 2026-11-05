#include <algorithm>
#include <set>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int findTheDistanceValue(std::vector<int> const &arr1, std::vector<int> const &arr2, int d) const
    {
        std::set<int> numbers2(arr2.cbegin(), arr2.cend());
        size_t result = 0;
        for (int number : arr1)
        {
            int minValue = INT_MAX;
            auto upperBound = numbers2.upper_bound(number);
            if (upperBound != numbers2.cend())
                minValue = *upperBound - number;
            if (upperBound != numbers2.cbegin())
                minValue = std::min(minValue, number - *std::prev(upperBound, 1));
            if (minValue > d)
                ++result;
        }
        return static_cast<int>(result);
    }
};

}

namespace FindDistanceValueBetweenTwoArraysTask
{

TEST(FindDistanceValueBetweenTwoArraysTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.findTheDistanceValue({4, 5, 8}, {10, 9, 1, 8}, 2));
    ASSERT_EQ(2, solution.findTheDistanceValue({1, 4, 2, 3}, {-4, -3, 6, 10, 20, 30}, 3));
    ASSERT_EQ(1, solution.findTheDistanceValue({2, 1, 100, 3}, {-5, -2, 10, -3, 7}, 6));
}

}