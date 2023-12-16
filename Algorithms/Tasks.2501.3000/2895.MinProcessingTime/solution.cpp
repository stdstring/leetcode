#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minProcessingTime(std::vector<int> const &processorTime, std::vector<int> const &tasks) const
    {
        std::vector<int> sortedProcessorTime(processorTime);
        std::ranges::sort(sortedProcessorTime);
        std::vector<int> sortedTasks(tasks);
        std::ranges::sort(sortedTasks, std::greater<int>());
        int processingTime = INT_MIN;
        for (size_t processor = 0; processor < sortedProcessorTime.size(); ++processor)
            processingTime = std::max(processingTime, sortedProcessorTime[processor] + sortedTasks[4 * processor]);
        return processingTime;
    }
};

}

namespace MinProcessingTimeTask
{

TEST(MinProcessingTimeTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(16, solution.minProcessingTime({8, 10}, {2, 2, 3, 1, 8, 7, 4, 5}));
    ASSERT_EQ(23, solution.minProcessingTime({10, 20}, {2, 3, 1, 2, 5, 8, 4, 3}));
}

}