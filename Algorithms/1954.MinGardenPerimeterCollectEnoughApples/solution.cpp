#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] long long minimumPerimeterByIterating(long long neededApples) const
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

    [[nodiscard]] long long minimumPerimeterByBinarySearch(long long neededApples) const
    {
        long long left = 0;
        long long right = 1;
        long long rightCount = calcApplesOnSquare(right);
        while (rightCount < neededApples)
        {
            right *= 10;
            rightCount = calcApplesOnSquare(right);
        }
        while ((right - left) > 1)
        {
            const long long middle = (right + left) / 2;
            const long long middleCount = calcApplesOnSquare(middle);
            if (middleCount == neededApples)
                return 8 * middle;
            if (middleCount < neededApples)
                left = middle;
            else
                right = middle;
        }
        return 8 * right;
    }

private:
    [[nodiscard]] long long calcApplesOnLayer(long long layerSize) const
    {
        //const long long innerSize = layerSize - 1;
        //return 4 * (layerSize) + 4 * (2 * layerSize) + 8 * (layerSize * innerSize + (1 + innerSize) * innerSize / 2);
        return 12 * layerSize * layerSize;
    }

    long long calcApplesOnSquare(long long size) const
    {
        // 1^2 + 2^2 + ... + n^2 = n * (n + 1) * (2 * n + 1) / 6
        return 2 * size * (size + 1) * (2 * size + 1);
    }
};

}

namespace
{

void checkMinimumPerimeter(long long neededApples, long long expectedPerimeter)
{
    constexpr Solution solution;
    ASSERT_EQ(expectedPerimeter, solution.minimumPerimeterByIterating(neededApples));
    ASSERT_EQ(expectedPerimeter, solution.minimumPerimeterByBinarySearch(neededApples));
}

}

namespace MinGardenPerimeterCollectEnoughApplesTask
{

TEST(MinGardenPerimeterCollectEnoughApplesTaskTests, Examples)
{
    constexpr Solution solution;
    checkMinimumPerimeter(1, 8);
    checkMinimumPerimeter(13, 16);
    checkMinimumPerimeter(1000000000, 5040);
}

}