#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int peakIndexInMountainArray(std::vector<int> const &arr) const
    {
        for (size_t index = 1; index < arr.size(); ++index)
        {
            if (arr[index] < arr[index - 1])
                return static_cast<int>(index - 1);
        }
        return -1;
    }
};

}

namespace PeakIndexInMountainArrayTask
{

TEST(PeakIndexInMountainArrayTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(1, solution.peakIndexInMountainArray({0, 1, 0}));
    ASSERT_EQ(1, solution.peakIndexInMountainArray({0, 2, 1, 0}));
    ASSERT_EQ(1, solution.peakIndexInMountainArray({0, 10, 5, 2}));
}

}