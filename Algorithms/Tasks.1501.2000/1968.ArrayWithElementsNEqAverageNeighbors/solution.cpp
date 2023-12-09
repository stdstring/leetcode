#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> rearrangeArray(std::vector<int> const &nums) const
    {
        std::vector<int> numbers(nums);
        std::ranges::sort(numbers);
        std::vector<int> result;
        result.reserve(numbers.size());
        for (size_t left = 0, right = numbers.size() - 1; left <= right ; ++left, --right)
        {
            result.emplace_back(numbers[left]);
            if (left != right)
                result.emplace_back(numbers[right]);
        }
        return result;
    }
};

}

namespace ArrayWithElementsNEqAverageNeighborsTask
{

TEST(ArrayWithElementsNEqAverageNeighborsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({1, 5, 2, 4, 3}), solution.rearrangeArray({1, 2, 3, 4, 5}));
    ASSERT_EQ(std::vector<int>({0, 9, 2, 7, 6}), solution.rearrangeArray({6, 2, 0, 9, 7}));
}

}