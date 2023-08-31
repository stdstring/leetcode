#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int tupleSameProduct(std::vector<int> const &nums) const
    {
        std::unordered_map<int, size_t> productMap;
        for (size_t index1 = 0; index1 < nums.size(); ++index1)
        {
            for (size_t index2 = index1 + 1; index2 < nums.size(); ++index2)
                ++productMap[nums[index1] * nums[index2]];
        }
        size_t result = 0;
        for (auto const &[_, count] : productMap)
            result += (count - 1) * count / 2;
        return 8 * static_cast<int>(result);
    }
};

}

namespace TupleWithSameProductTask
{

TEST(TupleWithSameProductTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(8, solution.tupleSameProduct({2, 3, 4, 6}));
    ASSERT_EQ(16, solution.tupleSameProduct({1, 2, 4, 5, 10}));
}

TEST(TupleWithSameProductTaskTests, CustomExamples)
{
    constexpr Solution solution;
    ASSERT_EQ(40, solution.tupleSameProduct({2, 12, 4, 6, 3, 8}));
}

}