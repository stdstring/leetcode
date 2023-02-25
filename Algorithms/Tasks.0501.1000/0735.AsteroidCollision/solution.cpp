#include <list>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::vector<int> asteroidCollision(std::vector<int> const &asteroids) const
    {
        std::list<int> survivedAsteroids;
        for (int asteroid : asteroids)
        {
            const int asteroidValue = std::abs(asteroid);
            while (!survivedAsteroids.empty() && (asteroid < 0) && (survivedAsteroids.back() > 0) && (asteroidValue > survivedAsteroids.back()))
                survivedAsteroids.pop_back();
            if (!survivedAsteroids.empty() && (asteroid < 0) && (survivedAsteroids.back() > 0))
            {
                if (asteroidValue == survivedAsteroids.back())
                    survivedAsteroids.pop_back();
            }
            else
                survivedAsteroids.push_back(asteroid);
        }
        std::vector<int> result(survivedAsteroids.cbegin(), survivedAsteroids.cend());
        return result;
    }
};

}


namespace AsteroidCollisionTask
{

TEST(AsteroidCollisionTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<int>({5, 10}), solution.asteroidCollision({5, 10, -5}));
    ASSERT_EQ(std::vector<int>(), solution.asteroidCollision({8, -8}));
    ASSERT_EQ(std::vector<int>({10}), solution.asteroidCollision({10, 2, -5}));
    ASSERT_EQ(std::vector<int>({-2, -1, 1, 2}), solution.asteroidCollision({-2, -1, 1, 2}));
}

}