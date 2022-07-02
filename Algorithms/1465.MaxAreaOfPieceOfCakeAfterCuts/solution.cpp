#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maxArea(int h, int w, std::vector<int> const &horizontalCuts, std::vector<int> const &verticalCuts) const
    {
        std::vector<int> sortedHorizontalCuts(horizontalCuts);
        sortedHorizontalCuts.push_back(0);
        sortedHorizontalCuts.push_back(h);
        std::sort(sortedHorizontalCuts.begin(), sortedHorizontalCuts.end());
        std::vector<int> sortedVerticalCuts(verticalCuts);
        sortedVerticalCuts.push_back(0);
        sortedVerticalCuts.push_back(w);
        std::sort(sortedVerticalCuts.begin(), sortedVerticalCuts.end());
        int maxH = 0;
        for (size_t index = 1; index < sortedHorizontalCuts.size(); ++index)
            maxH = std::max(maxH, sortedHorizontalCuts[index] - sortedHorizontalCuts[index - 1]);
        int maxW = 0;
        for (size_t index = 1; index < sortedVerticalCuts.size(); ++index)
            maxW = std::max(maxW, sortedVerticalCuts[index] - sortedVerticalCuts[index - 1]);
        constexpr int64_t modValue = 1000000007;
        const int64_t maxArea = (0LL + maxH) * (0LL + maxW);
        return static_cast<int>(maxArea % modValue);
    }
};

}

namespace MaxAreaOfPieceOfCakeAfterCutsTask
{

TEST(MaxAreaOfPieceOfCakeAfterCutsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(4, solution.maxArea(5, 4, {1, 2, 4}, {1, 3}));
    ASSERT_EQ(6, solution.maxArea(5, 4, {3, 1}, {1}));
    ASSERT_EQ(9, solution.maxArea(5, 4, {3}, {3}));
}

}