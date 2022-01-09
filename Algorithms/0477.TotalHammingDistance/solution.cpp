#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int totalHammingDistance(std::vector<int> const &nums) const
    {
        constexpr size_t maxPower = 31;
        std::vector<int> masks(maxPower);
        masks[0] = 1;
        for (size_t power = 1; power < maxPower; ++power)
            masks[power] = masks[power - 1] << 1;
        std::vector<size_t> oneBitsCount(maxPower);
        for (int number : nums)
        {
            for (size_t power = 0; power < maxPower; ++power)
            {
                if ((number & masks[power]) > 0)
                    ++oneBitsCount[power];
            }
        }
        size_t distance = 0;
        for (size_t power = 0; power < maxPower; ++power)
            distance += oneBitsCount[power] * (nums.size() - oneBitsCount[power]);
        return static_cast<int>(distance);
    }
};

}

namespace TotalHammingDistanceTask
{

TEST(TotalHammingDistanceTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(6, solution.totalHammingDistance({4, 14, 2}));
    ASSERT_EQ(4, solution.totalHammingDistance({4, 14, 4}));
}

}