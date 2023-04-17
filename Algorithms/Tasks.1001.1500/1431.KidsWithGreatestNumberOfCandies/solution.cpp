#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<bool> kidsWithCandies(std::vector<int> const &candies, int extraCandies) const
    {
        const int maxCandies = *std::max_element(candies.cbegin(), candies.cend());
        std::vector<bool> result(candies.size(), false);
        for (size_t index = 0; index < candies.size(); ++index)
            result[index] = (candies[index] + extraCandies) >= maxCandies;
        return result;
    }
};

}

namespace KidsWithGreatestNumberOfCandiesTask
{

TEST(KidsWithGreatestNumberOfCandiesTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<bool>({true, true, true, false, true}), solution.kidsWithCandies({2, 3, 5, 1, 3}, 3));
    ASSERT_EQ(std::vector<bool>({true, false, false, false, false}), solution.kidsWithCandies({4, 2, 1, 1, 2}, 1));
    ASSERT_EQ(std::vector<bool>({true, false, true}), solution.kidsWithCandies({12, 1, 12}, 10));
}

}