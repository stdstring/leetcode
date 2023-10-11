#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> filterRestaurants(std::vector<std::vector<int>> const &restaurants, int veganFriendly, int maxPrice, int maxDistance) const
    {
        constexpr size_t id = 0;
        constexpr size_t rating = 1;
        constexpr size_t veganStatus = 2;
        constexpr size_t price = 3;
        constexpr size_t distance = 4;
        std::vector<size_t> destIndices;
        for (size_t index = 0; index < restaurants.size(); ++index)
        {
            const bool isVeganStatusSuitable = (veganFriendly == 0) || (restaurants[index][veganStatus] == veganFriendly);
            if (isVeganStatusSuitable && (restaurants[index][price] <= maxPrice) && (restaurants[index][distance] <= maxDistance))
                destIndices.emplace_back(index);
        }
        auto sortFun = [&restaurants](size_t l, size_t r) { return (restaurants[l][rating] > restaurants[r][rating]) ||
                                                                        ((restaurants[l][rating] == restaurants[r][rating]) && (restaurants[l][id] > restaurants[r][id])); };
        std::ranges::sort(destIndices, sortFun);
        std::vector<int> destIds(destIndices.size(), 0);
        std::ranges::transform(std::as_const(destIndices), destIds.begin(), [&restaurants](size_t index) { return restaurants[index][id]; });
        return destIds;
    }
};

}

namespace FilterRestaurantsTask
{

TEST(FilterRestaurantsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({3, 1, 5}),
              solution.filterRestaurants({{1, 4, 1, 40, 10}, {2, 8, 0, 50, 5}, {3, 8, 1, 30, 4}, {4, 10, 0, 10, 3}, {5, 1, 1, 15, 1}}, 1, 50, 10));
    ASSERT_EQ(std::vector<int>({4, 3, 2, 1, 5}),
              solution.filterRestaurants({{1, 4, 1, 40, 10}, {2, 8, 0, 50, 5}, {3, 8, 1, 30, 4}, {4, 10, 0, 10, 3}, {5, 1, 1, 15, 1}}, 0, 50, 10));
    ASSERT_EQ(std::vector<int>({4, 5}),
              solution.filterRestaurants({{1, 4, 1, 40, 10}, {2, 8, 0, 50, 5}, {3, 8, 1, 30, 4}, {4, 10, 0, 10, 3}, {5, 1, 1, 15, 1}}, 0, 30, 3));
}

}