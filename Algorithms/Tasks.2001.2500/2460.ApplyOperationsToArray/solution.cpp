#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> applyOperations(std::vector<int> const &nums) const
    {
        std::vector<int> result(nums);
        for (size_t index = 0; index < nums.size() - 1; ++index)
        {
            if (result[index] == result[index + 1])
            {
                result[index] *= 2;
                result[index + 1] = 0;
            }
        }
        size_t current = 0;
        for (size_t index = 0; index < result.size(); ++index)
        {
            if (result[index] == 0)
                continue;
            result[current] = result[index];
            ++current;
        }
        for (;current < result.size(); ++current)
            result[current] = 0;
        return result;
    }
};

}

namespace ApplyOperationsToArrayTask
{

TEST(ApplyOperationsToArrayTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({1, 4, 2, 0, 0, 0}), solution.applyOperations({1, 2, 2, 1, 1, 0}));
}

}