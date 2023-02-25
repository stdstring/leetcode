#include <vector>

#include "gtest/gtest.h"

namespace
{

enum class MonotonicState { Unknown, Increasing, Decreasing };

class Solution
{
public:
    bool isMonotonic(std::vector<int> const &nums) const
    {
        MonotonicState monotonicState = MonotonicState::Unknown;
        int prevValue = nums.front();
        for (int number : nums)
        {
            if (number == prevValue)
                continue;
            switch (monotonicState)
            {
                case MonotonicState::Unknown:
                    monotonicState = number > prevValue ? MonotonicState::Increasing : MonotonicState::Decreasing;
                    break;
                case MonotonicState::Increasing:
                    if (number < prevValue)
                        return false;
                    break;
                case MonotonicState::Decreasing:
                    if (number > prevValue)
                        return false;
                    break;
            }
            prevValue = number;
        }
        return true;
    }
};

}

namespace MonotonicArrayTask
{

TEST(MonotonicArrayTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(true, solution.isMonotonic({1, 2, 2, 3}));
    ASSERT_EQ(true, solution.isMonotonic({6, 5, 4, 4}));
    ASSERT_EQ(false, solution.isMonotonic({1, 3, 2}));
    ASSERT_EQ(true, solution.isMonotonic({1, 2, 4, 5}));
    ASSERT_EQ(true, solution.isMonotonic({1, 1, 1}));
}

}