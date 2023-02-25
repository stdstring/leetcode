#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int findPairs(std::vector<int> const &nums, int k) const
    {
        std::unordered_map<int, size_t> numbersData;
        for (int number : nums)
            ++numbersData[number];
        size_t pairsCount = 0;
        for (const auto &data : numbersData)
        {
            if ((k == 0 && data.second > 1) || (k != 0 && numbersData.count(data.first + k) == 1))
                ++pairsCount;
        }
        return static_cast<int>(pairsCount);
    }
};

}

namespace KdiffPairsInArrayTasks
{

TEST(KdiffPairsInArrayTasksTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(2, solution.findPairs({3, 1, 4, 1, 5}, 2));
    ASSERT_EQ(4, solution.findPairs({1, 2, 3, 4, 5}, 1));
    ASSERT_EQ(1, solution.findPairs({1, 3, 1, 5, 4}, 0));
    ASSERT_EQ(2, solution.findPairs({1, 2, 4, 4, 3, 3, 0, 9, 2, 3}, 3));
    ASSERT_EQ(2, solution.findPairs({-1, -2, -3}, 1));
}

}