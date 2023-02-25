#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int minSteps(int n) const
    {
        const size_t totalCount = n;
        std::vector<size_t> steps(totalCount + 1, INT_MAX);
        steps[0] = steps[1] = 0;
        for (size_t initCount = 1; initCount <= totalCount / 2; ++initCount)
        {
            size_t stepsCount = steps[initCount] + 2;
            size_t charCount = 2 * initCount;
            while (charCount <= totalCount)
            {
                steps[charCount] = std::min(steps[charCount], stepsCount);
                ++stepsCount;
                charCount += initCount;
            }
        }
        return static_cast<int>(steps[n]);
    }
};

}


namespace TwoKeysKeyboardTask
{

TEST(TwoKeysKeyboardTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(3, solution.minSteps(3));
}

}
