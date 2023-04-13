#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minOperations(int n) const
    {
        std::vector<int> onePositions;
        for (int position = 0; n > 0; ++position, n >>= 1)
        {
            if ((n & 1) == 1)
                onePositions.emplace_back(position);
        }
        std::reverse(onePositions.begin(), onePositions.end());
        int operationCount = 0;
        while (!onePositions.empty())
        {
            ++operationCount;
            int current = onePositions.back();
            onePositions.pop_back();
            bool isGroup = false;
            while (!onePositions.empty() && (onePositions.back() == (current + 1)))
            {
                current = onePositions.back();
                onePositions.pop_back();
                isGroup = true;
            }
            if (isGroup)
                onePositions.emplace_back(current + 1);
        }
        return operationCount;
    }
};

}

namespace MinOpsReduceIntegerTo0Task
{

TEST(MinOpsReduceIntegerTo0TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.minOperations(39));
    ASSERT_EQ(3, solution.minOperations(54));
}

}