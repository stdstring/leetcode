#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] long long repairCars(std::vector<int> const &ranks, int cars) const
    {
        long long totalCars = cars;
        auto [minRank, maxRank] = std::ranges::minmax(ranks);
        std::vector<int> rankFreq(maxRank - minRank + 1, 0);
        for (int rank : ranks)
            ++rankFreq[rank - minRank];
        long long left = 1;
        long long right = 1LL * minRank * totalCars * totalCars;
        while (left < right)
        {
            const long long middle = (left + right) / 2;
            long long carsRepaired = 0;
            for (int rank = minRank; rank <= maxRank; ++rank)
            {
                if (rankFreq[rank - minRank] > 0)
                    carsRepaired += 1LL * rankFreq[rank - minRank] * static_cast<long long>(std::sqrt(middle / rank));
            }
            if (carsRepaired < cars)
                left = middle + 1;
            else
                right = middle;
        }
        return left;
    }
};

}

namespace MinTimeRepairCarsTask
{

TEST(MinTimeRepairCarsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(16, solution.repairCars({4, 2, 3, 1}, 10));
    ASSERT_EQ(16, solution.repairCars({5, 1, 8}, 6));
}

}