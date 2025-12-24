#include <algorithm>
#include <numeric>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minimumBoxes(std::vector<int> const &apple, std::vector<int> const &capacity) const
    {
        int totalApples = std::accumulate(apple.cbegin(), apple.cend(), 0);
        std::vector<int> sortedCapacity(capacity);
        std::ranges::sort(sortedCapacity, std::greater<int>());
        size_t result = 0;
        for (const int currentCapacity : sortedCapacity)
        {
            totalApples -= currentCapacity;
            ++result;
            if (totalApples <= 0)
                break;
        }
        return static_cast<int>(result);
    }
};

}

namespace AppleRedistributionIntoBoxesTask
{

TEST(AppleRedistributionIntoBoxesTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.minimumBoxes({1, 3, 2}, {4, 3, 1, 5, 2}));
    ASSERT_EQ(4, solution.minimumBoxes({5, 5, 5}, {2, 4, 2, 7}));
}

}