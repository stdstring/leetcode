#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] long long minimumPerimeter(long long neededApples) const
    {
        long long totalApples = 0;
        long long layerSize = 0;
        while (totalApples < neededApples)
        {
            ++layerSize;
            totalApples += calcApplesOnLayer(layerSize);
        }
        return 8 * layerSize;
    }

private:
    [[nodiscard]] long long calcApplesOnLayer(long long layerSize) const
    {
        const long long innerSize = layerSize - 1;
        return 4 * (layerSize) + 4 * (2 * layerSize) + 8 * (layerSize * innerSize + (1 + innerSize) * innerSize / 2);
    }
};

}

namespace MinGardenPerimeterCollectEnoughApplesTask
{

TEST(MinGardenPerimeterCollectEnoughApplesTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(8, solution.minimumPerimeter(1));
    ASSERT_EQ(16, solution.minimumPerimeter(13));
    ASSERT_EQ(5040, solution.minimumPerimeter(1000000000));
}

}