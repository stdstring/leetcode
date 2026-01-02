#include <unordered_set>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int repeatedNTimes(std::vector<int> const &nums) const
    {
        std::unordered_set<int> knownNumbers;
        for (int number : nums)
        {
            if (knownNumbers.contains(number))
                return number;
            knownNumbers.emplace(number);
        }
        return -1;
    }
};

}

namespace NRepeatedElementInSize2NArrayTask
{

TEST(NRepeatedElementInSize2NArrayTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.repeatedNTimes({1, 2, 3, 3}));
    ASSERT_EQ(2, solution.repeatedNTimes({2, 1, 2, 5, 3, 2}));
    ASSERT_EQ(5, solution.repeatedNTimes({5, 1, 5, 2, 5, 3, 5, 4}));
}

}