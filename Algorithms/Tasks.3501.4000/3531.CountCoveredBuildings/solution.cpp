#include <algorithm>
#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int countCoveredBuildings(int n, std::vector<std::vector<int>> const &buildings) const
    {
        std::unordered_map<int, std::vector<size_t>> verticalBuildings;
        std::unordered_map<int, std::vector<size_t>> horizontalBuildings;
        for (size_t index = 0; index < buildings.size(); ++index)
        {
            const int x = buildings[index][0];
            const int y = buildings[index][1];
            verticalBuildings[x].emplace_back(index);
            horizontalBuildings[y].emplace_back(index);
        }
        std::vector<int> coveredRaiting(buildings.size(), 0);
        auto verticalComp = [&buildings](size_t l, size_t r){ return buildings[l][1] < buildings[r][1]; };
        auto horizontalComp = [&buildings](size_t l, size_t r){ return buildings[l][0] < buildings[r][0]; };
        for (auto &[_, bindexes] : verticalBuildings)
        {
            std::ranges::sort(bindexes, verticalComp);
            for (size_t index = 1; index < bindexes.size() - 1; ++index)
                ++coveredRaiting[bindexes[index]];
        }
        for (auto &[_, bindexes] : horizontalBuildings)
        {
            std::ranges::sort(bindexes, horizontalComp);
            for (size_t index = 1; index < bindexes.size() - 1; ++index)
                ++coveredRaiting[bindexes[index]];
        }
        size_t result = 0;
        for (int value : coveredRaiting)
        {
            if (value == 2)
                ++result;
        }
        return static_cast<int>(result);
    }
};

}

namespace CountCoveredBuildingsTask
{

TEST(CountCoveredBuildingsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(1, solution.countCoveredBuildings(3, {{1, 2}, {2, 2}, {3, 2}, {2, 1}, {2, 3}}));
    ASSERT_EQ(0, solution.countCoveredBuildings(3, {{1, 1}, {1, 2}, {2, 1}, {2, 2}}));
    ASSERT_EQ(1, solution.countCoveredBuildings(5, {{1, 3}, {3, 2}, {3, 3}, {3, 5}, {5, 3}}));
}

}