#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] bool checkSubarraySum(std::vector<int> const &nums, int k) const
    {
        std::unordered_map<int, size_t> prefixRestPos;
        int sum = 0;
        for (size_t index = 0; index < nums.size(); ++index)
        {
            sum = (sum + nums[index]) % k;
            if ((sum == 0) && (index > 0))
                return true;
            auto iterator = prefixRestPos.find(sum);
            if (iterator == prefixRestPos.cend())
                prefixRestPos.emplace(sum, index);
            else
            {
                if ((index - iterator->second) > 1)
                    return true;
            }
        }
        return false;
    }
};

}

namespace ContinuousSubarraySumTask
{

TEST(ContinuousSubarraySumTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(true, solution.checkSubarraySum({23, 2, 4, 6, 7}, 6));
    ASSERT_EQ(true, solution.checkSubarraySum({23, 2, 6, 4, 7}, 6));
    ASSERT_EQ(false, solution.checkSubarraySum({23, 2, 6, 4, 7}, 13));
}

TEST(ContinuousSubarraySumTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(true, solution.checkSubarraySum({2, 4, 3}, 6));
    ASSERT_EQ(true, solution.checkSubarraySum({23, 2, 4, 6, 6}, 7));
}

}