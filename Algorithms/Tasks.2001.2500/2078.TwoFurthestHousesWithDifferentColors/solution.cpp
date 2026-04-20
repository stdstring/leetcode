#include <algorithm>
#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maxDistance(std::vector<int> const &colors) const
    {
        size_t result = 0;
        std::unordered_map<int, size_t> colorsMap;
        for (size_t index = 0; index < colors.size(); ++index)
        {
            for (auto const &[color, start] : colorsMap)
            {
                if (color != colors[index])
                    result = std::max(result, index - start);
            }
            if (!colorsMap.contains(colors[index]))
                colorsMap.emplace(colors[index], index);
        }
        return static_cast<int>(result);
    }
};

}

namespace TwoFurthestHousesWithDifferentColorsTask
{

TEST(TwoFurthestHousesWithDifferentColorsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.maxDistance({1, 1, 1, 6, 1, 1, 1}));
    ASSERT_EQ(4, solution.maxDistance({1, 8, 3, 8, 3}));
    ASSERT_EQ(1, solution.maxDistance({0, 1}));
}

}