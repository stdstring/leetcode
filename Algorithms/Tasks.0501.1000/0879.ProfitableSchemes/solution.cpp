#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int profitableSchemes(int n, int minProfit, std::vector<int> const &group, std::vector<int> const &profit) const
    {
        constexpr int modValue = 1000000007;
        std::vector<std::vector<int>> dpCurrent(n + 1, std::vector<int>(minProfit + 1, 0));
        dpCurrent[0][0] = 1;
        for (size_t index = 0; index < profit.size(); ++index)
        {
            std::vector<std::vector<int>> dpNext(n + 1, std::vector<int>(minProfit + 1, 0));
            for (int usedPeople = 0; usedPeople <= n; ++usedPeople)
            {
                for (int currentProfit = 0; currentProfit <= minProfit; ++currentProfit)
                {
                    dpNext[usedPeople][currentProfit] = (dpNext[usedPeople][currentProfit] + dpCurrent[usedPeople][currentProfit]) % modValue;
                    if ((n - usedPeople) >= group[index])
                    {
                        const int nextUsedPeople = usedPeople + group[index];
                        const int nextProfit = (currentProfit + profit[index]) > minProfit ? minProfit : currentProfit + profit[index];
                        dpNext[nextUsedPeople][nextProfit] = (dpNext[nextUsedPeople][nextProfit] + dpCurrent[usedPeople][currentProfit]) % modValue;
                    }
                }
            }
            std::swap(dpCurrent, dpNext);
        }
        int result = 0;
        for (std::vector<int> const& row : dpCurrent)
            result = (result + row.back()) % modValue;
        return result;
    }
};

}

namespace ProfitableSchemesTask
{

TEST(ProfitableSchemesTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.profitableSchemes(5, 3, {2, 2}, {2, 3}));
    ASSERT_EQ(7, solution.profitableSchemes(10, 5, {2, 3, 5}, {6, 7, 8}));
}

}