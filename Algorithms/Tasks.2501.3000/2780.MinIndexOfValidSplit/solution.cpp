#include <algorithm>
#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minimumIndex(std::vector<int> const &nums) const
    {
        std::unordered_map<int, size_t> numberCountMap;
        for (int number : nums)
            ++numberCountMap[number];
        auto comp = [](std::pair<int, size_t> const& l, std::pair<int, size_t> const& r) { return l.second < r.second; };
        const auto iterator = std::ranges::max_element(std::as_const(numberCountMap), comp);
        const int dominantNumber = iterator->first;
        const size_t dominantCount = iterator->second;
        size_t leftDominantCount = 0;
        for (size_t index = 0; index < nums.size(); ++index)
        {
            if (nums[index] == dominantNumber)
                ++leftDominantCount;
            const size_t leftSize = index + 1;
            const size_t rightSize = nums.size() - leftSize;
            const size_t rightDominantCount = dominantCount - leftDominantCount;
            if (((2 * leftDominantCount) > leftSize) && ((2 * rightDominantCount) > rightSize))
                return static_cast<int>(index);
        }
        return -1;
    }
};

}

namespace MinIndexOfValidSplitTask
{

TEST(MinIndexOfValidSplitTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.minimumIndex({1, 2, 2, 2}));
    ASSERT_EQ(4, solution.minimumIndex({2, 1, 3, 1, 1, 1, 7, 1, 2, 1}));
    ASSERT_EQ(-1, solution.minimumIndex({3, 3, 3, 3, 7, 2, 2}));
}

}