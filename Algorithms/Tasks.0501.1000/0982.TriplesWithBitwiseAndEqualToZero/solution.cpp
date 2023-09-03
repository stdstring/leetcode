#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int countTriplets(std::vector<int> const &nums) const
    {
        std::unordered_map<int, size_t> pairAndCountMap;
        for (size_t index1 = 0; index1 < nums.size(); ++index1)
        {
            for (size_t index2 = index1; index2 < nums.size(); ++index2)
                pairAndCountMap[nums[index1] & nums[index2]] += (index1 == index2 ? 1 : 2);
        }
        constexpr int maxPairValue = (1 << 16) - 1;
        size_t result = 0;
        for (const int number : nums)
        {
            for (int pairValue = 0; pairValue <= maxPairValue; ++pairValue)
            {
                if ((pairValue & number) != 0)
                    continue;
                auto iterator = pairAndCountMap.find(pairValue);
                if (iterator != pairAndCountMap.cend())
                    result += iterator->second;
            }
        }
        return static_cast<int>(result);
    }
};

}

namespace TriplesWithBitwiseAndEqualToZeroTask
{

TEST(TriplesWithBitwiseAndEqualToZeroTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(12, solution.countTriplets({2, 1, 3}));
    ASSERT_EQ(27, solution.countTriplets({0, 0, 0}));
}

}