#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<long long> maximumEvenSplit(long long finalSum) const
    {
        if (finalSum % 2 == 1)
            return {};
        std::vector<long long> evenIntegers;
        for (long long current = 2;; current += 2)
        {
            if ((2 * current + 2) > finalSum)
            {
                evenIntegers.push_back(finalSum);
                break;
            }
            evenIntegers.push_back(current);
            finalSum -= current;
        }
        return evenIntegers;
    }
};

}

namespace MaxSplitOfPositiveEvenIntegersTask
{

TEST(MaxSplitOfPositiveEvenIntegersTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<long long>({2, 4, 6}), solution.maximumEvenSplit(12));
    ASSERT_EQ(std::vector<long long>(), solution.maximumEvenSplit(7));
    ASSERT_EQ(std::vector<long long>({2, 4, 6, 16}), solution.maximumEvenSplit(28));
}

}