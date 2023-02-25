#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] bool asteroidsDestroyed(int mass, std::vector<int> const &asteroids) const
    {
        std::vector<int> sortedAsteroids(asteroids);
        std::sort(sortedAsteroids.begin(), sortedAsteroids.end());
        for (size_t index  = 0; index < sortedAsteroids.size() && mass < sortedAsteroids.back(); ++index)
        {
            const int asteroid = sortedAsteroids[index];
            if (mass < asteroid)
                return false;
            mass += asteroid;
        }
        return true;
    }
};

}

namespace DestroyingAsteroidsTask
{

TEST(DestroyingAsteroidsTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(true, solution.asteroidsDestroyed(10, {3, 9, 19, 5, 21}));
    ASSERT_EQ(false, solution.asteroidsDestroyed(5, {4, 9, 23, 4}));
}

}