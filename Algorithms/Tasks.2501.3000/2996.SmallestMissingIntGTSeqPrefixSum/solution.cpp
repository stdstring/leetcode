#include <unordered_set>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int missingInteger(std::vector<int> const &nums) const
    {
        int prefixSum = nums[0];
        for (size_t index = 1; index < nums.size(); ++index)
        {
            if (nums[index] == (nums[index - 1] + 1))
                prefixSum += nums[index];
            else
                break;
        }
        std::unordered_set<int> numbers(nums.cbegin(), nums.cend());
        for (int number = prefixSum; ; ++number)
        {
            if (!numbers.contains(number))
                return number;
        }
    }
};

}

namespace SmallestMissingIntGTSeqPrefixSumTask
{

TEST(SmallestMissingIntGTSeqPrefixSumTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(6, solution.missingInteger({1, 2, 3, 2, 5}));
    ASSERT_EQ(15, solution.missingInteger({3, 4, 5, 1, 12, 14, 13}));
}

TEST(SmallestMissingIntGTSeqPrefixSumTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(47, solution.missingInteger({46, 8, 2, 4, 1, 4, 10, 2, 4, 10, 2, 5, 7, 3, 1}));
}

}