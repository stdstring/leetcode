#include <algorithm>
#include <numeric>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] long long minimumRemoval(std::vector<int> const &beans) const
    {
        std::vector<int> sortedBeans(beans);
        std::ranges::sort(sortedBeans);
        const long long totalSum = std::accumulate(sortedBeans.cbegin(), sortedBeans.cend(), 0LL);
        long long bestResult = totalSum;
        size_t portionStart = 0;
        for (size_t index = 1; index < sortedBeans.size(); ++index)
        {
            if (sortedBeans[index] != sortedBeans[index - 1])
            {
                long long currentResult = totalSum - static_cast<long long>(sortedBeans.size() - portionStart) * sortedBeans[index - 1];
                bestResult = std::min(bestResult, currentResult);
                portionStart = index;
            }
        }
        return std::min(bestResult, totalSum - static_cast<long long>(sortedBeans.size() - portionStart) * sortedBeans.back());
    }
};

}

namespace RemovingMinNumberMagicBeansTask
{

TEST(RemovingMinNumberMagicBeansTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(4, solution.minimumRemoval({4, 1, 6, 5}));
    ASSERT_EQ(7, solution.minimumRemoval({2, 10, 3, 2}));
}

}