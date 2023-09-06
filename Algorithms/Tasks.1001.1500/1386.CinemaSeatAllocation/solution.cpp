#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maxNumberOfFamilies(int n, std::vector<std::vector<int>> const &reservedSeats) const
    {
        std::unordered_map<int, int> reservedMap;
        for (std::vector<int> const &reservedSeat : reservedSeats)
            reservedMap[reservedSeat[0]] |= (1 << (reservedSeat[1] - 1));
        constexpr int bothFreeMask = 0b111111110;
        constexpr int leftFreeMask = 0b11110;
        constexpr int middleFreeMask = 0b1111000;
        constexpr int rightFreeMask = 0b111100000;
        int fourPersonGroupsCount = 2 * n;
        for (auto const &[_, reservedMask] : reservedMap)
        {
            const int totalFreeMask = ~reservedMask;
            if ((totalFreeMask & bothFreeMask) == bothFreeMask)
                continue;
            fourPersonGroupsCount -= ((totalFreeMask & leftFreeMask) == leftFreeMask) ||
                                     ((totalFreeMask & middleFreeMask) == middleFreeMask) ||
                                     ((totalFreeMask & rightFreeMask) == rightFreeMask) ? 1 : 2;
        }
        return fourPersonGroupsCount;
    }
};

}

namespace CinemaSeatAllocationTask
{

TEST(CinemaSeatAllocationTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(4, solution.maxNumberOfFamilies(3, {{1, 2}, {1, 3}, {1, 8}, {2, 6}, {3, 1}, {3, 10}}));
    ASSERT_EQ(2, solution.maxNumberOfFamilies(2, {{2, 1}, {1, 8}, {2, 6}}));
    ASSERT_EQ(4, solution.maxNumberOfFamilies(4, {{4,3},{1,4},{4,6},{1,7}}));
}

TEST(CinemaSeatAllocationTaskTests, CustomExamples)
{
    constexpr Solution solution;
    ASSERT_EQ(0, solution.maxNumberOfFamilies(1, {{1, 5}, {1, 7}, {1, 9}}));
}

}