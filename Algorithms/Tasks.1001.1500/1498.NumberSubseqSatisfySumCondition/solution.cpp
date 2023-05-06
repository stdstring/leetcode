#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int numSubseq(std::vector<int> const &nums, int target) const
    {
        std::vector<int> numbers(nums);
        std::sort(numbers.begin(), numbers.end());
        if (2 * numbers.front() > target)
            return 0;
        size_t left = 0;
        size_t right = numbers.size() - 1;
        while ((numbers[left] + numbers[right]) > target)
            --right;
        constexpr int modValue = 1000000007;
        std::vector<int> powers(right - left + 1, 0);
        powers[0] = 1;
        for (size_t index = 1; index < powers.size(); ++index)
            powers[index] = (2 * powers[index - 1]) % modValue;
        int result = 0;
        while (left < right)
        {
            if ((numbers[left] + numbers[right]) <= target)
            {
                result = (result + powers[right - left]) % modValue;
                ++left;
            }
            else
                --right;
        }
        if (2 * numbers[left] <= target)
            result = (result + 1) % modValue;
        return result;
    }
};

}

namespace NumberSubseqSatisfySumConditionTask
{

TEST(NumberSubseqSatisfySumConditionTaskTests, Examples2)
{
    constexpr Solution solution;
    ASSERT_EQ(4, solution.numSubseq({3, 5, 6, 7}, 9));
    ASSERT_EQ(6, solution.numSubseq({3, 3, 6, 8}, 10));
    ASSERT_EQ(61, solution.numSubseq({2, 3, 3, 4, 6, 7}, 12));
}

}