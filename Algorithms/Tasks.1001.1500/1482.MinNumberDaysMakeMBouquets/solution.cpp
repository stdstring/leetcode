#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minDays(std::vector<int> const &bloomDay, int m, int k) const
    {
        const size_t usedFlowers = static_cast<size_t>(m) * k;
        if (usedFlowers > bloomDay.size())
            return -1;
        std::vector<int> sortedBoomDays(bloomDay);
        std::ranges::sort(sortedBoomDays);
        size_t left = usedFlowers - 1;
        size_t right = bloomDay.size() - 1;
        while (left < right)
        {
            const size_t middle = (left + right) / 2;
            if (canMakeBouquets(bloomDay, sortedBoomDays[middle], m, k))
                right = middle;
            else
                left = middle + 1;
        }
        return sortedBoomDays[left];
    }

private:
    [[nodiscard]] bool canMakeBouquets(std::vector<int> const &bloomDay, int currentDay, int m, int k) const
    {
        const size_t bouquetSize = k;
        const size_t expectedBouquets = m;
        for (size_t index = 0, actualBouquets = 0, bouquetStart = 0; index < bloomDay.size(); ++index)
        {
            if (bloomDay[index] > currentDay)
            {
                bouquetStart = index + 1;
                continue;
            }
            if ((index - bouquetStart + 1) == bouquetSize)
            {
                ++actualBouquets;
                bouquetStart = index + 1;
            }
            if (actualBouquets == expectedBouquets)
                return true;
        }
        return false;
    }
};

}

namespace MinNumberDaysMakeMBouquetsTask
{

TEST(MinNumberDaysMakeMBouquetsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.minDays({1, 10, 3, 10, 2}, 3, 1));
    ASSERT_EQ(-1, solution.minDays({1, 10, 3, 10, 2}, 3, 2));
    ASSERT_EQ(12, solution.minDays({7, 7, 7, 7, 12, 7, 7}, 2, 3));
}

}