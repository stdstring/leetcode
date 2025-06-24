#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> findKDistantIndices(std::vector<int> const &nums, int key, int k) const
    {
        const int numberCount = static_cast<int>(nums.size());
        std::vector<int> result;
        for (int index = 0; index < numberCount; ++index)
        {
            if (nums[index] != key)
                continue;
            const int left = std::max(result.empty() ? 0 : (result.back() + 1), index - k);
            const int right = std::min(numberCount - 1, index + k);
            for (int neighborIndex = left; neighborIndex <= right; ++neighborIndex)
                result.emplace_back(neighborIndex);
        }
        return result;
    }
};

}

namespace FindAllKDistantIndicesInArrayTask
{

TEST(FindAllKDistantIndicesInArrayTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({1, 2, 3, 4, 5, 6}), solution.findKDistantIndices({3, 4, 9, 1, 3, 9, 5}, 9, 1));
    ASSERT_EQ(std::vector<int>({0, 1, 2, 3, 4}), solution.findKDistantIndices({2, 2, 2, 2, 2}, 2, 2));
}

}