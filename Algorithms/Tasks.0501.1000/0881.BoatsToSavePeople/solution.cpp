#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int numRescueBoats(std::vector<int> const &people, int limit) const
    {
        std::vector<int> sortedPeople(people);
        std::sort(sortedPeople.begin(), sortedPeople.end());
        size_t boatsCount = 0;
        size_t front = 0;
        size_t back = sortedPeople.size() - 1;
        while (front < back)
        {
            if (sortedPeople[front] + sortedPeople[back] <= limit)
                ++front;
            --back;
            ++boatsCount;
        }
        return static_cast<int>(boatsCount + (front == back ? 1 : 0));
    }
};

}

namespace BoatsToSavePeopleTask
{

TEST(BoatsToSavePeopleTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(1, solution.numRescueBoats({1, 2}, 3));
    ASSERT_EQ(3, solution.numRescueBoats({3, 2, 2, 1}, 3));
    ASSERT_EQ(4, solution.numRescueBoats({3, 5, 3, 4}, 5));
}

}