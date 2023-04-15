#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maxNumOfMarkedIndices(std::vector<int> const &nums) const
    {
        std::vector<int> sortedNumbers(nums);
        std::sort(sortedNumbers.begin(), sortedNumbers.end());
        int markedIndicesCount = 0;
        for (size_t left = 0, right = nums.size() / 2 + (nums.size() % 2 == 0 ? 0 : 1); right < nums.size(); ++right)
        {
            if ((2 * sortedNumbers[left]) <= sortedNumbers[right])
            {
                ++left;
                markedIndicesCount += 2;
            }
        }
        return markedIndicesCount;
    }
};

}

namespace FindMaxNumberOfMarkedIndicesTask
{

TEST(FindMaxNumberOfMarkedIndicesTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.maxNumOfMarkedIndices({3, 5, 2, 4}));
    ASSERT_EQ(4, solution.maxNumOfMarkedIndices({9, 2, 5, 4}));
    ASSERT_EQ(0, solution.maxNumOfMarkedIndices({7, 6, 8}));
}

TEST(FindMaxNumberOfMarkedIndicesTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(26, solution.maxNumOfMarkedIndices({42, 83, 48, 10, 24, 55, 9, 100, 10, 17,
                                                  17, 99, 51, 32, 16, 98, 99, 31, 28, 68,
                                                  71, 14, 64, 29, 15, 40}));
    ASSERT_EQ(58, solution.maxNumOfMarkedIndices({57, 40, 57, 51, 90, 51, 68, 100, 24, 39,
                                                  11, 85, 2, 22, 67, 29, 74, 82, 10, 96,
                                                  14, 35, 25, 76, 26, 54, 29, 44, 63, 49,
                                                  73, 50, 95, 89, 43, 62, 24, 88, 88, 36,
                                                  6, 16, 14, 2, 42, 42, 60, 25, 4, 58,
                                                  23, 22, 27, 26, 3, 79, 64, 20, 92}));
}

}