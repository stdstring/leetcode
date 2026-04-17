#include <algorithm>
#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minMirrorPairDistance(std::vector<int> const &nums) const
    {
        size_t minDistance = nums.size();
        std::unordered_map<int, size_t> numbers;
        for (size_t rIndex = 0; rIndex < nums.size(); ++rIndex)
        {
            const size_t index = nums.size() - 1 - rIndex;
            int reversed = reverse(nums[index]);
            auto iterator = numbers.find(reversed);
            if (iterator != numbers.cend())
                minDistance = std::min(minDistance, iterator-> second - index);
            numbers[nums[index]] = index;
        }
        return minDistance == nums.size() ? -1 :static_cast<int>(minDistance);
    }

private:
    [[nodiscard]] int reverse(int number) const
    {
        int result = 0;
        for (; number > 0; number /= 10)
            result = 10 * result + (number % 10);
        return result;
    }
};

}

namespace MinAbsDistanceBetweenMirrorPairsTask
{

TEST(MinAbsDistanceBetweenMirrorPairsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(1, solution.minMirrorPairDistance({12, 21, 45, 33, 54}));
    ASSERT_EQ(1, solution.minMirrorPairDistance({120, 21}));
    ASSERT_EQ(-1, solution.minMirrorPairDistance({21, 120}));
}

TEST(MinAbsDistanceBetweenMirrorPairsTaskTests, CustomExamples)
{
    constexpr Solution solution;
    ASSERT_EQ(1, solution.minMirrorPairDistance({11, 11}));
}

}