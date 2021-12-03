#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int longestMountain(std::vector<int> const &arr) const
    {
        size_t mountainSize = 0;
        size_t mountainStart = arr.size();
        bool hasPeak = false;
        for (size_t index = 1; index < arr.size(); ++index)
        {
            if (mountainStart == arr.size())
            {
                if (arr[index] > arr[index - 1])
                    mountainStart = index - 1;
            }
            else if (hasPeak)
            {
                if (arr[index] >= arr[index - 1])
                {
                    mountainSize = std::max(mountainSize, index - mountainStart);
                    mountainStart = arr[index] > arr[index - 1] ? index - 1 : arr.size();
                    hasPeak = false;
                }
            }
            else
            {
                if (arr[index] == arr[index - 1])
                    mountainStart = arr.size();
                if (arr[index] < arr[index - 1])
                    hasPeak = true;
            }
        }
        if (hasPeak)
            mountainSize = std::max(mountainSize, arr.size() - mountainStart);
        return static_cast<int>(mountainSize);
    }
};

}

namespace LongestMountainInArrayTask
{

TEST(LongestMountainInArrayTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(5, solution.longestMountain({2, 1, 4, 7, 3, 2, 5}));
    ASSERT_EQ(0, solution.longestMountain({2, 2, 2}));
}

}