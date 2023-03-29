#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maxSatisfaction(std::vector<int> const &satisfaction) const
    {
        std::vector<int> negativeSatisfaction;
        std::vector<int> nonnegativeSatisfaction;
        int nonnegativeSatisfactionSum = 0;
        for (int dishSatisfaction : satisfaction)
        {
            if (dishSatisfaction >= 0)
            {
                nonnegativeSatisfaction.emplace_back(dishSatisfaction);
                nonnegativeSatisfactionSum += dishSatisfaction;
            }
            else
                negativeSatisfaction.emplace_back(dishSatisfaction);
        }
        if (nonnegativeSatisfactionSum == 0)
            return 0;
        std::sort(nonnegativeSatisfaction.begin(), nonnegativeSatisfaction.end());
        std::sort(negativeSatisfaction.begin(), negativeSatisfaction.end(), std::greater<int>());
        int result = 0;
        for (size_t index = 0; index < nonnegativeSatisfaction.size(); ++index)
            result += static_cast<int>(index + 1) * nonnegativeSatisfaction[index];
        int negativeSatisfactionSum = 0;
        for (size_t index = 0; (index < negativeSatisfaction.size()) && (std::abs(negativeSatisfactionSum + negativeSatisfaction[index]) < nonnegativeSatisfactionSum); ++index)
        {
            negativeSatisfactionSum += negativeSatisfaction[index];
            result += (nonnegativeSatisfactionSum + negativeSatisfactionSum);
        }
        return result;
    }
};

}

namespace ReducingDishesTask
{

TEST(ReducingDishesTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(14, solution.maxSatisfaction({-1, -8, 0, 5, -9}));
    ASSERT_EQ(20, solution.maxSatisfaction({4, 3, 2}));
    ASSERT_EQ(0, solution.maxSatisfaction({-1, -4, -5}));
}

}