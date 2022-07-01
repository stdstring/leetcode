#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maximumUnits(std::vector<std::vector<int>> const &boxTypes, int truckSize) const
    {
        std::vector<std::vector<int>> sortedBoxes(boxTypes);
        std::sort(sortedBoxes.begin(), sortedBoxes.end(), [](std::vector<int> const &l, std::vector<int> const &r){ return l[1] > r[1]; });
        int unitsNumber = 0;
        for (std::vector<int> const &box : sortedBoxes)
        {
            const int boxCount = std::min(truckSize, box[0]);
            unitsNumber += (boxCount * box[1]);
            truckSize -= boxCount;
            if (truckSize == 0)
                break;
        }
        return unitsNumber;
    }
};

}

namespace MaxUnitsOnTruckTask
{

TEST(MaxUnitsOnTruckTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(8, solution.maximumUnits({{1, 3}, {2, 2}, {3, 1}}, 4));
    ASSERT_EQ(91, solution.maximumUnits({{5, 10}, {2, 5}, {4, 7}, {3, 9}}, 10));
}

}