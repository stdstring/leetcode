#include <algorithm>
#include <functional>
#include <numeric>
#include <vector>

#include "gtest/gtest.h"

namespace
{

struct Segment
{
    Segment(size_t size, size_t negativeCount, size_t firstNegative, size_t lastNegative) : Size(size), NegativeCount(negativeCount), FirstNegative(firstNegative), LastNegative(lastNegative)
    {
    }

    size_t Size;
    size_t NegativeCount;
    size_t FirstNegative;
    size_t LastNegative;
};

class Solution
{
public:
    int maxProduct(std::vector<int> const &nums) const
    {
        if (nums.size() == 1)
            return nums.front();
        int best = INT_MIN;
        for (size_t index = 0; index < nums.size();)
        {
            if (nums[index] == 0)
            {
                best = std::max(0, best);
                ++index;
            }
            else
            {
                Segment segment(calcSegment(nums, index));
                best = std::max(best, calcBest(nums, index, segment));
                index += segment.Size;
            }
        }
        return best;
    }

private:
    Segment calcSegment(std::vector<int> const &nums, size_t start) const
    {
        Segment segment(0, 0, nums.size(), nums.size());
        while (start < nums.size() && nums[start] != 0)
        {
            if (nums[start] < 0)
            {
                ++segment.NegativeCount;
                if (segment.FirstNegative == nums.size())
                    segment.FirstNegative = start;
                segment.LastNegative = start;
            }
            ++segment.Size;
            ++start;
        }
        return segment;
    }

    int calcBest(std::vector<int> const &nums, size_t start, Segment const &segment) const
    {
        if (segment.Size == 1)
            return nums[start];
        if (segment.NegativeCount % 2 == 0)
            return std::accumulate(nums.begin() + start, nums.begin() + start + segment.Size, 1, std::multiplies<>());
        const int product1 = std::accumulate(nums.begin() + start, nums.begin() + segment.LastNegative, 1, std::multiplies<>());
        const int product2 = std::accumulate(nums.begin() + segment.FirstNegative + 1, nums.begin() + start + segment.Size, 1, std::multiplies<>());
        return std::max(product1, product2);
    }
};

}

namespace MaximumProductSubarrayTask
{

TEST(MaximumProductSubarrayTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(6, solution.maxProduct({2, 3, -2, 4}));
    ASSERT_EQ(0, solution.maxProduct({-2, 0, -1}));
}

TEST(MaximumProductSubarrayTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(24, solution.maxProduct({2, -5, -2, -4, 3}));
    ASSERT_EQ(2, solution.maxProduct({0, 2}));
}

}