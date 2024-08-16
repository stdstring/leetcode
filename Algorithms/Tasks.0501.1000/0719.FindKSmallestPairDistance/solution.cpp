#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int smallestDistancePair(std::vector<int> const &nums, int k) const
    {
        std::vector<int> numbers(nums);
        std::ranges::sort(numbers);
        const size_t kPairPos = k;
        int left = 0;
        int right = numbers.back() - numbers.front();
        while (left < right)
        {
            int middle = (left + right) / 2;
            size_t pairsCount = calcPairCount(numbers, middle);
            if (pairsCount < kPairPos)
                left = middle + 1;
            else
                right = middle;
        }
        return left;
    }

private:
    [[nodiscard]] size_t calcPairCount(std::vector<int> const &numbers, int distance) const
    {
        size_t pairsCount = 0;
        for (size_t start = 0, end = 0; end < numbers.size(); ++end)
        {
            while ((numbers[end] - numbers[start]) > distance)
                ++start;
            pairsCount += (end - start);
        }
        return pairsCount;
    }
};

}

namespace FindKSmallestPairDistanceTask
{

TEST(FindKSmallestPairDistanceTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(0, solution.smallestDistancePair({1, 3, 1}, 1));
    ASSERT_EQ(0, solution.smallestDistancePair({1, 1, 1}, 2));
    ASSERT_EQ(5, solution.smallestDistancePair({1, 6, 1}, 3));
}

}